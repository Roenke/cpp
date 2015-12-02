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

void print(std::ostream& os, lazy_string const& str)
{
    os << str.buffer_.get_data() << std::endl;
}

lazy_string concat(lazy_string const& str1, lazy_string const& str2)
{
    auto new_size = str1.get_size() + str2.get_size();
    auto new_buffer = new char[new_size + 1];
    strcpy(&new_buffer[0], str1.buffer_.get_data());
    strcpy(&new_buffer[str1.get_size() - 1], str2.buffer_.get_data());
    new_buffer[new_size] = '\0';
    lazy_string new_str(new_buffer);
    return new_str;
}

