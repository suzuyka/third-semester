#pragma once
#include <string>

class CelestialBody {
public:
    std::string name;
    virtual ~CelestialBody() = default;
    CelestialBody(const std::string& n) : name(n) {}
    virtual bool isPlanet() const { return false; }
    virtual bool isAsteroid() const { return false; }
};
