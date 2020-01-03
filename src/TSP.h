#pragma once

#include <cmath>
#include <vector>

using City = std::pair<double, double>;
using Cities = std::vector<City>;

using Route = std::vector<size_t>;

inline
double distance(const City& a, const City& b)
{
   return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

inline
double length(const Route& route, const size_t numberOfCities, const std::vector<double>& distanceMatrix)
{
    auto first = route.begin();
    if (first == route.end())
        return 0;
    auto second = ++route.begin();

    double tmp = 0;
    while (second != route.end())
    {
        tmp += distanceMatrix[(*first) + numberOfCities * (*second)];
        ++first;
        ++second;
    }
    tmp += distanceMatrix[route.front() + numberOfCities * route.back()];

    return tmp;
}

class ITSP
{
public:
    ///Reset the current progress and start again.
    virtual void reset() = 0;

    ///Improve the current route.
    virtual void iterate() = 0;

    ///return the current route
    virtual const Route& getCurrentRoute() const = 0;

    ///Is the algorithm finished? No further or only small improvements.
    virtual bool isFinished() const = 0;
};
