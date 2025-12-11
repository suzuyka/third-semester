#pragma once
#include "Corporation.h"

class TechTrader : public Corporation {
public:
    TechTrader(const std::string& n) : Corporation(n) {}
    void executeTurn(std::vector<std::unique_ptr<CelestialBody>>& bodies) override;
};
