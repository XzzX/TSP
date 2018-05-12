#include "Input.h"

#include <SFML/Window.hpp>

#include <cassert>

Input::Input(const std::shared_ptr<sf::Window>& window)
   : window_(window)
{
   assert(window_);
}

void Input::pollEvents()
{
   // check all the window's events that were triggered since the last iteration of the loop
   sf::Event event;
   while (window_->pollEvent(event))
   {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
         window_->close();
   }
}
