#pragma once
#include "Corporation.h"

class MinerCompany : public Corporation {
public:
    MinerCompany(const std::string& n) : Corporation(n) {}
    void executeTurn(std::vector<std::unique_ptr<CelestialBody>>& bodies) override;
};
