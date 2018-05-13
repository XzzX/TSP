#pragma once

#include "Event.h"

#include <memory>
#include <queue>

namespace sf
{
class Window;
}

class Input
{
public:
    explicit Input(const std::shared_ptr<sf::Window>& window);

    bool pollEvents(Event& event);
private:
    std::shared_ptr<sf::Window> window_;
    std::queue<Event> events_;
};
