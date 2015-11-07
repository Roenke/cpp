#pragma once
#include "my_stream.h"
#include <fstream>

class my_stream_file
    : public my_stream
{
public:
    my_stream_file(std::string&);

    my_stream_file& operator<<(int&) override;
    my_stream_file& operator<<(double&) override;
    my_stream_file& operator<<(std::string const&) override;

private:
    std::ofstream output_;
};