#pragma once

#include <memory>

namespace sf
{
class Window;
}

class Input
{
public:
    explicit Input(const std::shared_ptr<sf::Window>& window);

    void pollEvents();
private:
    std::shared_ptr<sf::Window> window_;
};
