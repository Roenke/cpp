#include "my_ostream_con.h"
#include <iostream>

my_ostream_con& my_ostream_con::operator<<(int value)
{
    std::cout << value;
    return *this;
}

my_ostream_con& my_ostream_con::operator<<(double value)
{
    std::cout << value;
    return *this;
}

my_ostream_con& my_ostream_con::operator<<(std::string const& value)
{
    std::cout << value;
    return *this;
}
