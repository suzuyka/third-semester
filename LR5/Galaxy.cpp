#include "Galaxy.h"
#include "Planet.h"

void Galaxy::addPlanet(std::unique_ptr<Planet> p) {
    bodies.push_back(std::move(p));
}

void Galaxy::addAsteroid(std::unique_ptr<Asteroid> a) {
    bodies.push_back(std::move(a));
}

void Galaxy::addRoute(int from, int to, double fuelCost, double safety) {
    routes.emplace_back(from, to, fuelCost, safety);
    routes.emplace_back(to, from, fuelCost, safety);
}

void Galaxy::simulateTurn(std::vector<std::unique_ptr<Corporation>>& corps) {
    for (auto& b : bodies) {
        if (b->isPlanet()) {
            static_cast<Planet*>(b.get())->produce();
        }
    }

    for (auto& corp : corps) {
        corp->executeTurn(bodies);
    }
}
