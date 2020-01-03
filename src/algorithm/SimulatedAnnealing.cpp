#include "SimulatedAnnealing.h"

#include "common/debug.h"
#include "common/random.h"

#include <cassert>
#include <limits>
#include <numeric>

SimulatedAnnealing::SimulatedAnnealing(size_t numberOfCities,
                                       const std::shared_ptr<const std::vector<double>> &distanceMatrix)
        : numberOfCities_(numberOfCities), distanceMatrix_(distanceMatrix), route_(numberOfCities)
{
    reset();
}

void SimulatedAnnealing::reset()
{
    std::iota(route_.begin(), route_.end(), 0);
    currentLength_ = length(route_, numberOfCities_, *distanceMatrix_);
}

void SimulatedAnnealing::iterate()
{
    auto firstIdx = intRandom(0, numberOfCities_ - 1);
    auto secondIdx = intRandom(0, numberOfCities_ - 1);

    std::swap(route_[firstIdx], route_[secondIdx]);
    auto newLength = length(route_, numberOfCities_, *distanceMatrix_);

    if (newLength < currentLength_)
    {
        //accept unconditionally
        currentLength_ = newLength;
    } else
    {
        if ((exp( -(newLength - currentLength_) / temperature_)) >= realRandom(0, 1))
        {
            currentLength_ = newLength;
        } else
        {
            //revert the change
            std::swap(route_[firstIdx], route_[secondIdx]);
        }
    }
}
