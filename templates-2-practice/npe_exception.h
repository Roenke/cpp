#pragma once
#include <string>

namespace my_ptrs
{
    struct npe_exception
        : std::runtime_error
    {
        npe_exception();
        npe_exception(std::string const& what);
    };
}; /* my_ptrs */
