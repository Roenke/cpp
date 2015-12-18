#include "my_ostream_file.h"

my_ostream_file::my_ostream_file(std::string const& filename)
    : os_(filename)
{}

my_ostream_file& my_ostream_file::operator<<(int value)
{
    os_ << value;
    return *this;
}

my_ostream_file& my_ostream_file::operator<<(double value)
{
    os_ << value;
    return *this;
}

my_ostream_file& my_ostream_file::operator<<(std::string const& value)
{
    os_ << value;
    return *this;
}

