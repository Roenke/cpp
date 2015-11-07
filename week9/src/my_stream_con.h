#pragma once
#include "my_stream.h"

class my_stream_con
    : public my_stream
{
public:
    my_stream_con();

    my_stream_con& operator<<(int&) override;
    my_stream_con& operator<<(double&) override;
    my_stream_con& operator<<(std::string const&) override;
};
