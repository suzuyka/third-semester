#pragma once
#include <vector>
#include <memory>
#include "CelestialBody.h"
#include "Corporation.h"

struct Route {
    int from, to;
    double fuelCost;
    double safety;
    Route(int f, int t, double fc, double s = 1.0) : from(f), to(t), fuelCost(fc), safety(s) {}
};

class Galaxy {
public:
    std::vector<std::unique_ptr<CelestialBody>> bodies;
    std::vector<Route> routes;

    void addPlanet(std::unique_ptr<Planet> p);
    void addAsteroid(std::unique_ptr<Asteroid> a);
    void addRoute(int from, int to, double fuelCost, double safety = 1.0);
    void simulateTurn(std::vector<std::unique_ptr<Corporation>>& corps);
};
