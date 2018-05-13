#pragma once

#include "TSP.h"

#include <memory>

class GreedyRoute
{
public:
    GreedyRoute(const std::shared_ptr<Cities>& cities);
    GreedyRoute(const GreedyRoute& gr) = default;
    GreedyRoute(GreedyRoute&& gr) = default;
    GreedyRoute& operator=(const GreedyRoute& gr) = default;
    GreedyRoute& operator=(GreedyRoute&& gr) = default;

    void optimize();
    inline const Route& getOptimalRoute() const { return route_; }
private:
    std::shared_ptr<Cities> cities_;
    std::vector<bool> visited_;
    Route route_;
};
