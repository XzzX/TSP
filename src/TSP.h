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
