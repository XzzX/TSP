#include "Greedy.h"

#include "TSP.h"

GreedyRoute::GreedyRoute(const std::shared_ptr<Cities>& cities)
   : cities_(cities)
{}

void GreedyRoute::optimize()
{
   if (route_.size() < cities_->size())
   {
      route_.emplace_back(route_.size());
   }
}
