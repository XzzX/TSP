#include "TSP.h"

#include "algorithm/Greedy.h"
#include "algorithm/InOrder.h"

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
   std::generate_n( std::back_inserter(
           *cities),
           n,
           [](){return City(intRandom(0,100), intRandom(0,100));});
   return cities;
}

int main()
{
   const int numberOfCities = 10;
   const int interval = 2000;

   auto cities = createCities(numberOfCities);
   GreedyRoute route(cities);

   Display display(std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 800), "My window"));
   Input input(display.getWindow());

   // run the program as long as the window is open
   while (display.isOpen())
   {
      auto start = std::chrono::high_resolution_clock::now();

      Event ev;
      while (input.pollEvents(ev))
      {
         switch (ev)
         {
         case Event::Restart:
            cities = createCities(numberOfCities);
            route = GreedyRoute(cities);
            break;
         }
      }

      route.optimize();
      display.display(*cities, route.getOptimalRoute());

      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = end-start;
      std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(interval) - elapsed);
   }

   return 0;
}
