#pragma once

#include "TSP.h"

#include <memory>

class GreedyRoute
{
public:
    GreedyRoute(const std::shared_ptr<Cities>& cities);

    void optimize();
    inline const Route& getOptimalRoute() const { return route_; }
private:
    const std::shared_ptr<Cities> cities_;
    Route route_;
};
