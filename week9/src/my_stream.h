#pragma once
#include <string.h>
#include <fstream>

class my_stream
{
public:
    virtual ~my_stream(){};

    virtual my_stream& operator<<(int&)                = 0;
    virtual my_stream& operator<<(double&)             = 0;
    virtual my_stream& operator<<(std::string const&)  = 0;
};
