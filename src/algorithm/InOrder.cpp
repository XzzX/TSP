#include "InOrder.h"

#include "TSP.h"

InOrder::InOrder(const std::shared_ptr<Cities>& cities)
   : cities_(cities)
{}

void InOrder::optimize()
{
   if (route_.size() < cities_->size())
   {
      route_.emplace_back(route_.size());
   }
}
