#include "my_stream_file.h"

my_stream_file::my_stream_file(std::string& filename)
    : output_(filename)
{
}

my_stream_file& my_stream_file::operator<<(int& value)
{
    return *this;
}
my_stream_file& my_stream_file::operator<<(double& value)
{
    return *this;
}
my_stream_file& my_stream_file::operator<<(std::string const& value)
{
    return *this;
}