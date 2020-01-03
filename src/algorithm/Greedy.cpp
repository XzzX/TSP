#include "Greedy.h"

#include "TSP.h"

#include "common/debug.h"
#include "common/random.h"

#include <cassert>
#include <limits>

GreedyRoute::GreedyRoute(size_t numberOfCities, const std::shared_ptr<const std::vector<double>>& distanceMatrix)
   : numberOfCities_(numberOfCities)
   , distanceMatrix_(distanceMatrix)
   , visited_(numberOfCities, false)
{}

void GreedyRoute::reset()
{
    std::fill(visited_.begin(), visited_.end(), false);
    route_.clear();
}

void GreedyRoute::iterate()
{
   ASSERT_EQUAL(numberOfCities_, visited_.size());
   if (route_.size() < numberOfCities_)
   {
      if (route_.empty())
      {
         route_.emplace_back(intRandom(0, numberOfCities_));
         visited_[route_[0]] = true;
         return;
      }

      size_t newCity = std::numeric_limits<size_t>::max();
      double d = std::numeric_limits<double>::max();
      for (size_t i = 0; i < numberOfCities_; ++i)
      {
         if (visited_[i]) continue;
         ASSERT_NOT_EQUAL(route_.back(), i);
         auto dtmp = (*distanceMatrix_)[route_.back() + i * numberOfCities_];
         if (dtmp < d)
         {
            d = dtmp;
            newCity = i;
         }
      }
      ASSERT_NOT_EQUAL(newCity, std::numeric_limits<size_t>::max());
      route_.emplace_back(newCity);
      visited_[newCity] = true;
   }
}
