#include "event.h"

event::event()
{
}

void event::subscribe(std::function<void(std::string)> func)
{
    listeners_.push_back(func);
}

void event::fire(std::string const& arg)
{
    for(auto const& listener : listeners_)
    {
        listener(arg);
    }
}
