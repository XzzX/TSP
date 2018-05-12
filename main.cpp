#include "Greedy.h"
#include "TSP.h"

#include "Display.h"
#include "Input.h"

#include <chrono>
#include <functional>
#include <random>
#include <thread>

int main()
{
   static std::default_random_engine generator( std::chrono::system_clock::now().time_since_epoch().count() );
   std::uniform_real_distribution<double> distribution(0.0,100);
   auto rnd = std::bind(distribution, generator);

   std::shared_ptr<Cities> cities = std::make_shared<Cities>();
   for (auto i = 0; i<7; ++i)
   {
      cities->emplace_back(rnd(), rnd());
   }

   GreedyRoute route(cities);

   Display display(std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 800), "My window"));
   Input input(display.getWindow());

   // run the program as long as the window is open
   while (display.isOpen())
   {
      auto start = std::chrono::high_resolution_clock::now();

      route.optimize();
      input.pollEvents();
      display.display(*cities, route.getOptimalRoute());

      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = end-start;
      std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1000) - elapsed);
   }

   return 0;
}
