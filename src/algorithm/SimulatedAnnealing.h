#pragma once

#include "TSP.h"

#include <memory>

class SimulatedAnnealing : public ITSP
{
public:
    static constexpr int defaultInterval = 1;

    SimulatedAnnealing(const size_t numberOfCities, const std::shared_ptr<const std::vector<double>>& distanceMatrix);
    SimulatedAnnealing(const SimulatedAnnealing& gr) = default;
    SimulatedAnnealing(SimulatedAnnealing&& gr) = default;
    SimulatedAnnealing& operator=(const SimulatedAnnealing& gr) = default;
    SimulatedAnnealing& operator=(SimulatedAnnealing&& gr) = default;

    void reset() override;
    void iterate() override;
    inline const Route& getCurrentRoute() const override { return route_; }
    bool isFinished() const override {return numberOfCities_ == route_.size();}

    void setCurrentRoute(const Route& route) {route_ = route;}
private:
    size_t numberOfCities_;
    std::shared_ptr<const std::vector<double>> distanceMatrix_;
    Route route_;
    double currentLength_;
    double temperature_ = 1;
};
