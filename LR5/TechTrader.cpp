#include "TechTrader.h"

void TechTrader::executeTurn(std::vector<std::unique_ptr<CelestialBody>>& bodies) {
    for (auto& b : bodies) {
        if (!b->isPlanet()) continue;
        Planet* p = static_cast<Planet*>(b.get());
        if (p->techLevel < 5) continue;

        if (p->storedResources > static_cast<double>(p->demand) * 0.8) {
            double sold = p->storedResources - static_cast<double>(p->demand) * 0.8;
            profit += sold * p->getPrice() * 1.2;
            p->storedResources = static_cast<double>(p->demand) * 0.8;
        }
    }
}
