#include "random.h"

#include <chrono>
#include <random>

std::default_random_engine generator( std::chrono::system_clock::now().time_since_epoch().count() );

int intRandom(const int lowerBound, const int upperBound)
{
    std::uniform_int_distribution<int> distribution(lowerBound,upperBound);
    return distribution(generator);
}
double realRandom(const double lowerBound, const double upperBound)
{
    std::uniform_real_distribution<double> distribution(lowerBound,upperBound);
    return distribution(generator);
}
