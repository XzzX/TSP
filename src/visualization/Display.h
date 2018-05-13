#pragma once

#include "TSP.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>

class Display
{
public:
    explicit Display(const std::shared_ptr<sf::RenderWindow>& window);

    void display(const Cities& cities, const Route& route);

    inline const std::shared_ptr<sf::RenderWindow>& getWindow() const { return window_; }
    inline bool isOpen() const { return window_->isOpen(); }
private:
  std::shared_ptr<sf::RenderWindow> window_;
  sf::View view_{sf::FloatRect(0,0,100,100)};
};
