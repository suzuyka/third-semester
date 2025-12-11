#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "Planet.h"
#include "Asteroid.h"
#include "LogisticsCompany.h"
#include "TechTrader.h"
#include "MinerCompany.h"
#include "Galaxy.h"
using namespace std;

int main() {
    cout << "Галактическая экономика: Империя звёзд\n";
    int turns = 10;
    int nPlanets, nAsteroids, nCorps;

    cout << "Введите количество планет: ";
    cin >> nPlanets;
    cout << "Введите количество астероидов: ";
    cin >> nAsteroids;
    cout << "Введите количество корпораций: ";
    cin >> nCorps;

    Galaxy galaxy;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disProd(5, 50);
    uniform_int_distribution<> disDem(10, 60);
    uniform_int_distribution<> disTech(1, 10);
    uniform_int_distribution<> disCost(50, 200);

    vector<string> resources = {"metal", "energy", "tech", "food"};
    for (int i = 0; i < nPlanets; ++i) {
        string res = resources[i % resources.size()];
        galaxy.addPlanet(make_unique<Planet>(
            "Планета_" + to_string(i),
            res,
            disProd(gen),
            disDem(gen),
            disTech(gen)
        ));
    }

    for (int i = 0; i < nAsteroids; ++i) {
        galaxy.addAsteroid(make_unique<Asteroid>(
            "Астероид_" + to_string(i),
            "rare_metal",
            disCost(gen)
        ));
    }

    vector<unique_ptr<Corporation>> corps;
    for (int i = 0; i < nCorps; ++i) {
        cout << "Тип корпорации (" << i+1 << "): 1=Logistics, 2=Tech, 3=Miner: ";
        int type; cin >> type;
        string name = "Корп_" + to_string(i);
        if (type == 1) corps.push_back(make_unique<LogisticsCompany>(name));
        else if (type == 2) corps.push_back(make_unique<TechTrader>(name));
        else corps.push_back(make_unique<MinerCompany>(name));
    }

    for (int i = 0; i < nPlanets; ++i) {
        for (int j = i + 1; j < nPlanets; ++j) {
            galaxy.addRoute(i, j, 5.0 + (i + j) % 3);
        }
    }

    for (int turn = 1; turn <= turns; ++turn) {
        cout << "\n--- Ход " << turn << " ---\n";
        galaxy.simulateTurn(corps);

        for (auto& c : corps) {
            cout << c->name << " прибыль: " << c->profit << "\n";
        }
    }

    auto winner = max_element(corps.begin(), corps.end(),
        [](const auto& a, const auto& b) { return a->profit < b->profit; });
    cout << "\nПобедитель: " << (*winner)->name
              << " с прибылью: " << (*winner)->profit << "\n";

    return 0;
}
