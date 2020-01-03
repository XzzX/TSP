#include "Greedy.h"

#include "TSP.h"

#include "common/debug.h"
#include "common/random.h"

#include <cassert>
#include <limits>

GreedyRoute::GreedyRoute(const std::shared_ptr<Cities>& cities)
   : cities_(cities)
   , visited_(cities_->size(), false)
{}

void GreedyRoute::optimize()
{
   ASSERT_EQUAL(cities_->size(), visited_.size());
   if (route_.size() < cities_->size())
   {
      if (route_.empty())
      {
         route_.emplace_back(intRandom(0, cities_->size()));
         visited_[route_[0]] = true;
         return;
      }

      size_t newCity = std::numeric_limits<size_t>::max();
      double d = std::numeric_limits<double>::max();
      for (size_t i = 0; i < cities_->size(); ++i)
      {
         if (visited_[i]) continue;
         ASSERT_NOT_EQUAL(route_.back(), i);
         auto dtmp = distance((*cities_)[route_.back()], (*cities_)[i]);
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
