#pragma once

#include "TSP.h"

#include <memory>

class GreedyRoute : public ITSP
{
public:
    explicit GreedyRoute(const size_t numberOfCities, const std::shared_ptr<const std::vector<double>>& distanceMatrix);
    GreedyRoute(const GreedyRoute& gr) = default;
    GreedyRoute(GreedyRoute&& gr) = default;
    GreedyRoute& operator=(const GreedyRoute& gr) = default;
    GreedyRoute& operator=(GreedyRoute&& gr) = default;

    void reset() override;
    void iterate() override;
    inline const Route& getCurrentRoute() const override { return route_; }
    bool isFinished() const override {return numberOfCities_ == route_.size();}
private:
    size_t numberOfCities_;
    std::shared_ptr<const std::vector<double>> distanceMatrix_;
    std::vector<bool> visited_;
    Route route_;
};
