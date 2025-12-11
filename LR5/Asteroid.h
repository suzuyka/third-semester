#pragma once
#include "CelestialBody.h"

class Asteroid : public CelestialBody {
public:
    int miningCost;
    std::string resourceType;

    Asteroid(const std::string& n, const std::string& res, int cost)
        : CelestialBody(n), miningCost(cost), resourceType(res) {}

    bool isAsteroid() const override { return true; }
};

