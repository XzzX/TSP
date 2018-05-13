#include "TSP.h"

#include "algorithm/Greedy.h"
#include "algorithm/InOrder.h"

#include "util/random.h"

#include "visualization/Display.h"
#include "visualization/Input.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <thread>

std::shared_ptr<Cities> createCities(const int n)
{
   std::shared_ptr<Cities> cities = std::make_shared<Cities>();
   for (auto i = 0; i<n; ++i)
   {
      cities->emplace_back(intRandom(0,100), intRandom(0,100));
   }
   return cities;
}

int main()
{
   std::shared_ptr<Cities> cities = createCities(7);
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
            cities = createCities(7);
            route = GreedyRoute(cities);
            break;
         }
      }

      route.optimize();
      display.display(*cities, route.getOptimalRoute());

      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = end-start;
      std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1000) - elapsed);
   }

   return 0;
}
