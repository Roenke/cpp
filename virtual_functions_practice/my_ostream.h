#pragma once
#include <string>

class my_ostream
{
public:
    virtual ~my_ostream()
    {}

    virtual my_ostream& operator<<(int) = 0;
    virtual my_ostream& operator<<(double) = 0;
    virtual my_ostream& operator<<(std::string const&) = 0;
};
