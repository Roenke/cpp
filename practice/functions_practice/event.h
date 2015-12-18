#pragma once
#include <string>
#include <functional>
#include <vector>

class event
{
public:
    event();

    void subscribe(std::function<void(std::string)>);
    void fire(std::string const&);

private:
    std::vector<std::function<void(std::string)>> listeners_;
};
