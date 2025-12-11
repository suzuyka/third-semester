#pragma once
#include "CelestialBody.h"
#include <algorithm>

class Planet : public CelestialBody {
public:
    int productivity;
    int demand;
    std::string resourceType;
    int techLevel;
    double storedResources;

    Planet(const std::string& n, const std::string& res, int prod, int dem, int tech)
        : CelestialBody(n), productivity(prod), demand(dem), resourceType(res),
          techLevel(tech), storedResources(0.0) {}

    bool isPlanet() const override { return true; }

    void produce() {
        storedResources += productivity;
    }

    double getPrice() const {
        double supply = storedResources;
        if (supply <= 0) return 100.0;
        return std::max(1.0, static_cast<double>(demand) / supply * 10.0);
    }
};
