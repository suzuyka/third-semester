#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

class CertificateDB {
private:
    pqxx::connection conn;
    pqxx::work txn;

public:
    CertificateDB(const string& conninfo) : conn(conninfo), txn(conn) {
        cout << "Connected to PostgreSQL database." << endl;
    }

    ~CertificateDB() {
        txn.abort();
        conn.close();
    }

    void showMenu() {
        cout << "\n=== СИСТЕМА УЧЕТА СЕРТИФИКАТОВ ИБ ===\n";
        cout << "1.  Все сертификаты (JOIN)\n";
        cout << "2.  Сертификаты по типу\n";
        cout << "3.  Сертификаты с истекающим сроком (30 дней)\n";
        cout << "4.  Количество сертификатов по типам (GROUP BY)\n";
        cout << "5.  Сертификаты по организации\n";
        cout << "6.  Владельцы с >1 сертификатом (HAVING)\n";
        cout << "7.  История изменений сертификата\n";
        cout << "8.  Сертификаты по статусу\n";
        cout << "9.  Сертификаты с отзывами\n";
        cout << "10. Сертификаты по отделу владельца\n";
        cout << "11. Добавить сертификат\n";
        cout << "12. Обновить сертификат\n";
        cout << "13. Удалить сертификат\n";
        cout << "0.  Выход\n";
        cout << "Выбор: ";
    }

    void query1_allCertificates() {
        cout << "\nВсе сертификаты с владельцами и типами\n";
        auto res = txn.exec(R"(
            SELECT c.serial_number, c.issue_date, c.expiry_date, c.status, 
                   o.name as owner, ct.name as type, org.name as org, c.notes
            FROM Certificates c
            JOIN Owners o ON c.owner_id = o.id
            JOIN CertificateTypes ct ON c.certificate_type_id = ct.id
            JOIN Organizations org ON c.organization_id = org.id
            ORDER BY c.issue_date DESC;
        )");
        printTable(res, {"Serial", "Выдан", "Истекает", "Статус", "Владелец", "Тип", "Организация", "Примечание"});
    }

    void query2_certByType() {
        string type;
        cout << "Введите тип сертификата: ";
        getline(cin, type);
        auto res = txn.exec_params(R"(
            SELECT c.serial_number, c.issue_date, o.name
            FROM Certificates c
            JOIN Owners o ON c.owner_id = o.id
            JOIN CertificateTypes ct ON c.certificate_type_id = ct.id
            WHERE ct.name = $1;
        )", type);
        printTable(res, {"Serial", "Дата выдачи", "Владелец"});
    }

    void query3_expiringSoon() {
        cout << "\nСертификаты истекают в 30 дней\n";
        auto res = txn.exec(R"(
            SELECT c.serial_number, c.expiry_date, o.name,
                   (c.expiry_date - CURRENT_DATE) as days_left
            FROM Certificates c
            JOIN Owners o ON c.owner_id = o.id
            WHERE c.expiry_date BETWEEN CURRENT_DATE AND CURRENT_DATE + INTERVAL '30 days'
            ORDER BY c.expiry_date;
        )");
        printTable(res, {"Serial", "Истекает", "Владелец", "Дней осталось"});
    }

    void query4_countByType() {
        cout << "\nКоличество по типам (GROUP BY)\n";
        auto res = txn.exec(R"(
            SELECT ct.name, COUNT(c.id) as count,
                   AVG(EXTRACT(EPOCH FROM (c.expiry_date - c.issue_date))/86400) as avg_days
            FROM CertificateTypes ct
            LEFT JOIN Certificates c ON ct.id = c.certificate_type_id
            GROUP BY ct.name
            ORDER BY count DESC;
        )");
        printTable(res, {"Тип", "Количество", "Средний срок (дни)"});
    }

    void query5_byOrganization() {
        string org;
        cout << "Введите организацию: ";
        getline(cin, org);
        auto res = txn.exec_params(R"(
            SELECT org.name, COUNT(c.id) as count, STRING_AGG(c.serial_number, ', ')
            FROM Organizations org
            LEFT JOIN Certificates c ON org.id = c.organization_id
            WHERE org.name ILIKE $1
            GROUP BY org.id, org.name;
        )", "%" + org + "%");
        printTable(res, {"Организация", "Количество", "Сертификаты"});
    }

    void query6_ownersManyCerts() {
        cout << "\nВладельцы с >1 сертификатом (HAVING)\n";
        auto res = txn.exec(R"(
            SELECT o.name, o.department, COUNT(c.id) as cert_count
            FROM Owners o
            JOIN Certificates c ON o.id = c.owner_id
            GROUP BY o.id, o.name, o.department
            HAVING COUNT(c.id) > 1;
        )");
        printTable(res, {"Владелец", "Отдел", "Количество"});
    }

    void query7_certHistory() {
        string serial;
        cout << "Введите serial_number сертификата: ";
        getline(cin, serial);
        auto res = txn.exec_params(R"(
            SELECT cl.action, cl.timestamp, c.serial_number, cl.details
            FROM CertificateLogs cl
            JOIN Certificates c ON cl.certificate_id = c.id
            WHERE c.serial_number = $1
            ORDER BY cl.timestamp DESC;
        )", serial);
        printTable(res, {"Действие", "Время", "Serial", "Детали"});
    }

    void query8_certByStatus() {
        string status;
        cout << "Введите статус (active, expired, revoked): ";
        getline(cin, status);
        auto res = txn.exec_params(R"(
            SELECT c.serial_number, c.status, o.name, ct.name
            FROM Certificates c
            JOIN Owners o ON c.owner_id = o.id
            JOIN CertificateTypes ct ON c.certificate_type_id = ct.id
            WHERE c.status = $1;
        )", status);
        printTable(res, {"Serial", "Статус", "Владелец", "Тип"});
    }

    void query9_certWithRevocation() {
        cout << "\nСертификаты с отзывами\n";
        auto res = txn.exec(R"(
            SELECT c.serial_number, cr.revocation_date, cr.reason
            FROM Certificates c
            JOIN CertificateRevocations cr ON c.id = cr.certificate_id;
        )");
        printTable(res, {"Serial", "Дата отзыва", "Причина"});
    }

    void query10_certByDepartment() {
        string dept;
        cout << "Введите отдел: ";
        getline(cin, dept);
        auto res = txn.exec_params(R"(
            SELECT c.serial_number, o.name, o.department
            FROM Certificates c
            JOIN Owners o ON c.owner_id = o.id
            WHERE o.department = $1;
        )", dept);
        printTable(res, {"Serial", "Владелец", "Отдел"});
    }

    void addCertificate() {
        string serial, issue, expiry, type_id, owner_id, org_id, status, notes;
        cout << "\nДобавление сертификата:\n";
        cout << "Serial: "; getline(cin, serial);
        cout << "Дата выдачи (YYYY-MM-DD): "; getline(cin, issue);
        cout << "Дата истечения (YYYY-MM-DD): "; getline(cin, expiry);
        cout << "Тип ID: "; getline(cin, type_id);
        cout << "Владелец ID: "; getline(cin, owner_id);
        cout << "Организация ID: "; getline(cin, org_id);
        cout << "Статус: "; getline(cin, status);
        cout << "Примечание: "; getline(cin, notes);

        auto res = txn.exec_params(R"(
            INSERT INTO Certificates (serial_number, issue_date, expiry_date, 
                                    certificate_type_id, owner_id, organization_id, status, notes)
            VALUES ($1, $2::date, $3::date, $4::int, $5::int, $6::int, $7, $8)
            RETURNING id;
        )", serial, issue, expiry, type_id, owner_id, org_id, status, notes);

        if (!res.empty()) {
            cout << "Сертификат добавлен! ID: " << res[0][0].c_str() << endl;
            txn.exec_params("INSERT INTO CertificateLogs (certificate_id, action, user_id, details) "
                        "VALUES ($1, 'INSERT', 1, 'Создан сертификат');", res[0][0].c_str());
        }
        txn.commit();
    }


    void updateCertificate() {
        string serial, new_expiry, new_status;
        cout << "\nОбновление сертификата:\n";
        cout << "Serial: "; getline(cin, serial);
        cout << "Новая дата истечения: "; getline(cin, new_expiry);
        cout << "Новый статус: "; getline(cin, new_status);

        auto res = txn.exec_params(R"(
            UPDATE Certificates 
            SET expiry_date = $2::date, status = $3
            WHERE serial_number = $1
            RETURNING id;
        )", serial, new_expiry, new_status);

        if (!res.empty()) {
            cout << "Сертификат обновлен! ID: " << res[0][0].c_str() << endl;
            txn.exec_params("INSERT INTO CertificateLogs (certificate_id, action, user_id, details) "
                        "VALUES ($1, 'UPDATE', 1, 'Обновлен срок и статус');", res[0][0].c_str());
        }
        txn.commit();
    }

    void deleteCertificate() {
        string serial;
        cout << "\nУдаление сертификата:\n";
        cout << "Serial: "; getline(cin, serial);

        auto res = txn.exec_params(R"(
            DELETE FROM Certificates 
            WHERE serial_number = $1
            RETURNING id;
        )", serial);

        if (!res.empty()) {
            cout << "Сертификат удален! ID: " << res[0][0].c_str() << endl;
            txn.exec_params("INSERT INTO CertificateLogs (certificate_id, action, user_id, details) "
                        "VALUES ($1, 'DELETE', 1, 'Сертификат удален');", res[0][0].c_str());
        }
        txn.commit();
    }


private:
    void printTable(const pqxx::result& res, const vector<string>& headers) {
        if (res.empty()) {
            cout << "Нет данных\n";
            return;
        }

        for (size_t i = 0; i < headers.size(); ++i) {
            cout << left << setw(20) << headers[i];
        }
        cout << endl;

        for (auto row : res) {
            for (size_t i = 0; i < row.size(); ++i) {
                cout << left << setw(20) << row[i].c_str();
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    try {
        CertificateDB db("dbname=certificates user=postgres password=yourpassword host=localhost");
        
        int choice;
        while (true) {
            db.showMenu();
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: db.query1_allCertificates(); break;
                case 2: db.query2_certByType(); break;
                case 3: db.query3_expiringSoon(); break;
                case 4: db.query4_countByType(); break;
                case 5: db.query5_byOrganization(); break;
                case 6: db.query6_ownersManyCerts(); break;
                case 7: db.query7_certHistory(); break;
                case 8: db.query8_certByStatus(); break;
                case 9: db.query9_certWithRevocation(); break;
                case 10: db.query10_certByDepartment(); break;
                case 11: db.addCertificate(); break;
                case 12: db.updateCertificate(); break;
                case 13: db.deleteCertificate(); break;
                case 0: cout << "Выход\n"; return 0;
                default: cout << "Неверный выбор\n";
            }
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}
