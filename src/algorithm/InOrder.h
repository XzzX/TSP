#pragma once

#include "TSP.h"

#include <memory>

class InOrder
{
public:
    InOrder(const std::shared_ptr<Cities>& cities);
    InOrder(const InOrder& gr) = default;
    InOrder(InOrder&& gr) = default;
    InOrder& operator=(const InOrder& gr) = default;
    InOrder& operator=(InOrder&& gr) = default;

    void optimize();
    inline const Route& getOptimalRoute() const { return route_; }
private:
    std::shared_ptr<Cities> cities_;
    Route route_;
};
