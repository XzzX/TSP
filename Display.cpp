#include "Display.h"

#include <cassert>

Display::Display(const std::shared_ptr<sf::RenderWindow>& window)
   : window_(window)
{
   assert(window_);
   window_->setView(view_);
}

void Display::display(const Cities& cities, const Route& route)
{
   // clear the window with black color
   window_->clear(sf::Color::Black);

   sf::CircleShape cityShape(1);
   // set the shape color to green
   cityShape.setFillColor(sf::Color(100, 250, 50));
   for (auto& city : cities)
   {
      cityShape.setPosition( city.first - cityShape.getRadius(), city.second - cityShape.getRadius() );
      window_->draw(cityShape);
   }

   if (!route.empty())
   {
      cityShape.setFillColor(sf::Color::Red);
      auto& firstCity = cities[route.front()];
      cityShape.setPosition( firstCity.first - cityShape.getRadius(), firstCity.second - cityShape.getRadius() );
      window_->draw(cityShape);

      cityShape.setFillColor(sf::Color::Blue);
      auto& lastCity = cities[route.back()];
      cityShape.setPosition( lastCity.first - cityShape.getRadius(), lastCity.second - cityShape.getRadius() );
      window_->draw(cityShape);
   }

   // draw everything here...
   std::vector<sf::Vertex> line;
   for (auto& item : route)
   {
      assert(item < cities.size());
      line.emplace_back( sf::Vector2f(cities[item].first, cities[item].second) );
   }

   window_->draw(&line[0], line.size(), sf::LinesStrip);

   // end the current frame
   window_->display();
}
