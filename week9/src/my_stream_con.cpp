#include "my_stream_con.h"
#include <iostream>
my_stream_con::my_stream_con()
{
}

my_stream_con& my_stream_con::operator<<(int& value)
{
    std::cout << value;
    return *this;
}
my_stream_con& my_stream_con::operator<<(double& value)
{
    std::cout << value;
    return *this;   
}
my_stream_con& my_stream_con::operator<<(std::string const& value)
{
    std::cout << value;
    return *this;
}