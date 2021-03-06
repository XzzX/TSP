#include "TSP.h"

#include "algorithm/Greedy.h"
#include "algorithm/InOrder.h"
#include "algorithm/SimulatedAnnealing.h"

#include "common/random.h"

#include "visualization/Display.h"
#include "visualization/Input.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>

std::shared_ptr<Cities> createCities(const int n)
{
    auto cities = std::make_shared<Cities>();
    std::generate_n(std::back_inserter(
            *cities),
                    n,
                    []() { return City(intRandom(0, 100), intRandom(0, 100)); });
    return cities;
}

std::shared_ptr<std::vector<double>> createDistanceMatrix(const std::shared_ptr<Cities> &cities)
{
    auto numberOfCities = cities->size();
    auto distanceMatrix = std::make_shared<std::vector<double>>(numberOfCities * numberOfCities);
    for (size_t i = 0; i < numberOfCities; ++i)
    {
        for (size_t j = 0; j < numberOfCities; ++j)
        {
            (*distanceMatrix)[i + j * numberOfCities] = distance((*cities)[i], (*cities)[j]);
        }
    }
    return distanceMatrix;
}

int main()
{
    const int numberOfCities = 100;
    int interval = 1;

    auto cities = createCities(numberOfCities);
    auto distanceMatrix = createDistanceMatrix(cities);
    std::shared_ptr<ITSP> route = std::make_shared<GreedyRoute>(numberOfCities, distanceMatrix);

    Display display(std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 800), "My window"));
    Input input(display.getWindow());

    auto lastIteration = std::chrono::high_resolution_clock::now();

    // run the program as long as the window is open
    while (display.isOpen())
    {
        Event ev;
        while (input.pollEvents(ev))
        {
            auto tmp = route;
            switch (ev)
            {
                case Event::Greedy:
                    route = std::make_shared<GreedyRoute>(numberOfCities, createDistanceMatrix(cities));
                    interval = GreedyRoute::defaultInterval;
                    display.setWindowTitle("Greedy");
                    break;
                case Event::SimulatedAnnealing:
                    route = std::make_shared<SimulatedAnnealing>(numberOfCities, createDistanceMatrix(cities));
                    route->setCurrentRoute(tmp->getCurrentRoute());
                    interval = SimulatedAnnealing::defaultInterval;
                    display.setWindowTitle("Simulated Annealing");
                    break;
                case Event::Restart:
                    cities = createCities(numberOfCities);
                    distanceMatrix = createDistanceMatrix(cities);
                    //route = GreedyRoute(numberOfCities, createDistanceMatrix(cities));
                    break;
                case Event::Reset:
                    route->reset();
                    break;
                case Event::Iterate:
                    route->iterate();
                    break;
            }
        }

        auto now = std::chrono::high_resolution_clock::now();
        if ((now - lastIteration) > std::chrono::duration<double, std::milli>(interval))
        {
            route->iterate();
            lastIteration = now;

            //for (auto idx : route.getCurrentRoute())
            //{
            //    std::cout << idx << " ";
            //}
            //std::cout << std::endl;

            //std::cout << length(route.getCurrentRoute(), numberOfCities, *distanceMatrix) << std::endl;
        }

        display.display(*cities, route->getCurrentRoute(),
                        length(route->getCurrentRoute(), numberOfCities, *distanceMatrix));

    }

    return 0;
}
