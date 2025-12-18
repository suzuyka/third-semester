-- Создание базы данных
CREATE DATABASE certificates;

-- Подключитесь к базе certificates и выполните:
\c certificates

-- Таблицы

CREATE TABLE Organizations (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    address TEXT
);

CREATE TABLE CertificateTypes (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    description TEXT
);

CREATE TABLE Owners (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    position VARCHAR(255),
    department VARCHAR(100),
    email VARCHAR(255)
);

CREATE TABLE Certificates (
    id SERIAL PRIMARY KEY,
    serial_number VARCHAR(50) UNIQUE NOT NULL,
    issue_date DATE NOT NULL,
    expiry_date DATE NOT NULL,
    certificate_type_id INT REFERENCES CertificateTypes(id),
    owner_id INT REFERENCES Owners(id),
    organization_id INT REFERENCES Organizations(id),
    status VARCHAR(20) DEFAULT 'active',
    notes TEXT
);

CREATE TABLE CertificateLogs (
    id SERIAL PRIMARY KEY,
    certificate_id INT REFERENCES Certificates(id),
    action VARCHAR(100),
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    user_id INT,
    details TEXT
);

-- Дополнительная таблица: CertificateRevocations (отзывы сертификатов)
CREATE TABLE CertificateRevocations (
    id SERIAL PRIMARY KEY,
    certificate_id INT REFERENCES Certificates(id),
    revocation_date DATE NOT NULL,
    reason TEXT,
    user_id INT
);

-- Тестовые данные

-- Организации
INSERT INTO Organizations (name, address) VALUES 
('Роскомнадзор', 'Москва'),
('ФСТЭК', 'Москва'),
('ФСБ', 'Москва'),
('Минцифры', 'Москва');

-- Типы сертификатов
INSERT INTO CertificateTypes (name, description) VALUES 
('SSL', 'Сертификат для HTTPS'),
('X.509', 'Общий стандарт сертификатов'),
('Kerberos', 'Сертификат для аутентификации'),
('IPsec', 'Сертификат для сетевой безопасности'),
('S/MIME', 'Сертификат для электронной почты');

-- Владельцы
INSERT INTO Owners (name, position, department, email) VALUES 
('Иванов И.И.', 'Специалист ИБ', 'Безопасность', 'ivanov@company.ru'),
('Петров П.П.', 'Инженер', 'ИТ', 'petrov@company.ru'),
('Сидорова А.В.', 'Администратор', 'Системы', 'sidorova@company.ru'),
('Козлов Д.Д.', 'Руководитель', 'Безопасность', 'kozlov@company.ru');

-- Сертификаты
INSERT INTO Certificates (serial_number, issue_date, expiry_date, certificate_type_id, owner_id, organization_id, status, notes) VALUES 
('SSL-001', '2025-01-01', '2026-01-01', 1, 1, 1, 'active', 'Основной SSL'),
('X509-002', '2025-02-01', '2027-02-01', 2, 2, 2, 'active', 'Для внутреннего ПО'),
('KERB-003', '2025-03-01', '2026-03-01', 3, 3, 3, 'expired', 'Устарел'),
('IPSEC-004', '2025-04-01', '2026-04-01', 4, 4, 4, 'active', 'Сетевая защита'),
('SMIME-005', '2025-05-01', '2026-05-01', 5, 1, 1, 'revoked', 'Отозван');

-- Журнал действий
INSERT INTO CertificateLogs (certificate_id, action, user_id, details) VALUES 
(1, 'INSERT', 1, 'Создан сертификат SSL-001'),
(2, 'UPDATE', 1, 'Обновлен срок действия'),
(3, 'DELETE', 1, 'Сертификат отозван'),
(4, 'INSERT', 2, 'Создан сертификат IPSEC-004'),
(5, 'INSERT', 2, 'Создан сертификат SMIME-005');

-- Отзывы сертификатов
INSERT INTO CertificateRevocations (certificate_id, revocation_date, reason, user_id) VALUES 
(5, '2025-06-01', 'Утечка ключа', 1),
(3, '2025-04-15', 'Устаревший стандарт', 2);

