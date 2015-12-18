#pragma once
#include "my_ostream.h"

class my_ostream_con
    : public my_ostream
{
public:
    my_ostream_con& operator<<(int) override;
    my_ostream_con& operator<<(double) override;
    my_ostream_con& operator<<(std::string const&) override;
};
