#include "npe_exception.h"

my_ptrs::npe_exception::npe_exception()
    : runtime_error("Attempt access by null pointer")
{}

my_ptrs::npe_exception::npe_exception(std::string const& what)
    : runtime_error(what)
{}
