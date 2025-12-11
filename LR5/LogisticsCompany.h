#pragma once
#include "Corporation.h"

class LogisticsCompany : public Corporation {
public:
    LogisticsCompany(const std::string& n) : Corporation(n) {}
    void executeTurn(std::vector<std::unique_ptr<CelestialBody>>& bodies) override;
};
