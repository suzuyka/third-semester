#include "LogisticsCompany.h"
#include <algorithm>

void LogisticsCompany::executeTurn(std::vector<std::unique_ptr<CelestialBody>>& bodies) {
    for (auto& from : bodies) {
        if (!from->isPlanet()) continue;
        Planet* pFrom = static_cast<Planet*>(from.get());
        if (pFrom->storedResources <= static_cast<double>(pFrom->productivity)) continue;

        for (auto& to : bodies) {
            if (!to->isPlanet()) continue;
            Planet* pTo = static_cast<Planet*>(to.get());
            if (pTo->resourceType != pFrom->resourceType) continue;
            if (pTo->storedResources >= static_cast<double>(pTo->demand)) continue;

            double transfer = std::min(
                pFrom->storedResources - static_cast<double>(pFrom->productivity),
                static_cast<double>(pTo->demand) - pTo->storedResources
            );
            if (transfer <= 0) continue;

            double price = (pFrom->getPrice() + pTo->getPrice()) / 2.0;
            double transportCost = transfer * price * 0.1;

            pFrom->storedResources -= transfer;
            pTo->storedResources += transfer;
            profit += transfer * price - transportCost;
        }
    }
}
