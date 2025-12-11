#include "MinerCompany.h"

void MinerCompany::executeTurn(std::vector<std::unique_ptr<CelestialBody>>& bodies) {
    for (auto& b : bodies) {
        if (!b->isAsteroid()) continue;
        Asteroid* a = static_cast<Asteroid*>(b.get());
        int mined = 10;
        profit += mined * 20.0 - a->miningCost;
    }
}
