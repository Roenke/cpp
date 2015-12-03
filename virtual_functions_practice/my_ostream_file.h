#pragma once
#include "my_ostream.h"
#include <fstream>

class my_ostream_file
    : public my_ostream
{
public:
    my_ostream_file(std::string const&);

    my_ostream_file& operator<<(int) override;
    my_ostream_file& operator<<(double) override;
    my_ostream_file& operator<<(std::string const&) override;
private:
    std::ofstream os_;
};
