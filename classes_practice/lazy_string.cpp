#define _CRT_SECURE_NO_WARNINGS
#include "lazy_string.h"
#include <cstring>
#include <exception>

lazy_string::lazy_string(const char* src)
    : buffer_(strlen(src) + 1)
{
    strcpy(buffer_.get_data(), src);
}

lazy_string::lazy_string(const lazy_string& src)
    : buffer_(src.buffer_)
{}

bool lazy_string::empty() const
{
    return buffer_.get_size() == 0;
}

size_t lazy_string::get_size() const
{
    return buffer_.get_size();
}

char lazy_string::get_at(size_t ix) const
{
    if(ix >= buffer_.get_size())
    {
        throw std::exception("out of memory");
    }
    return buffer_.get_data()[ix];
}
