#pragma once
#include <vector>
#include <memory>
#include "Planet.h"
#include "Asteroid.h"

class Corporation {
public:
    std::string name;
    double profit;
    virtual ~Corporation() = default;
    Corporation(const std::string& n) : name(n), profit(0.0) {}
    virtual void executeTurn(std::vector<std::unique_ptr<CelestialBody>>& bodies) = 0;
};
