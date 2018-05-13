#include "Input.h"

#include <SFML/Window.hpp>

#include <cassert>

Input::Input(const std::shared_ptr<sf::Window>& window)
   : window_(window)
{
   assert(window_);
}

bool Input::pollEvents(Event& event)
{
   // check all the window's events that were triggered since the last iteration of the loop
   sf::Event ev;
   while (window_->pollEvent(ev))
   {
      // "close requested" event: we close the window
      if (ev.type == sf::Event::Closed)
         window_->close();
      if (ev.type == sf::Event::KeyReleased)
      {
         if (ev.key.code == sf::Keyboard::Space)
            events_.push(Event::Restart);
      }
   }

   if (!events_.empty())
   {
      event = events_.front();
      events_.pop();
      return true;
   }
   return false;
}
