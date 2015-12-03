#define _CRT_SECURE_NO_WARNINGS
#include "lazy_string.h"
#include <cstring>
#include <exception>
#include <algorithm>

using namespace lazy;

lazy_string::lazy_string(const char* src)
    : buffer_(new shared_buffer(strlen(src) + 1))
{
    strcpy(buffer_->get_data(), src);
}

lazy_string::lazy_string(const lazy_string& src)
    : buffer_(new shared_buffer(*src.buffer_))
{}

lazy_string lazy_string::operator=(lazy_string src)
{
    delete buffer_;
    buffer_ = src.buffer_;
    return *this;
}

void lazy_string::set_at(size_t ix, char value)
{
    if(buffer_->get_data()[ix] != value)
    {
        auto buf_size = buffer_->get_size();
        auto new_buffer = new shared_buffer(buf_size);
        const char* old_string = buffer_->get_data();
        memcpy(new_buffer->get_data(), old_string, buf_size);
        new_buffer->get_data()[ix] = value;

        delete buffer_;
        buffer_ = new_buffer;
    }
}

bool lazy_string::empty() const
{
    return buffer_->get_size() == 0;
}

size_t lazy_string::get_size() const
{
    return buffer_->get_size();
}

char lazy_string::get_at(size_t ix) const
{
    if(ix >= buffer_->get_size())
    {
        throw std::exception("out of memory");
    }
    return buffer_->get_data()[ix];
}

bool lazy::find(lazy_string const& in, const char* what, size_t& result, size_t start_ix)
{
    auto what_size = strlen(what);
    for (size_t i = 0; i < in.get_size() - what_size; ++i)
    {
        size_t j;
        for (j = 0; j < what_size && in.get_at(j + i) == what[j]; ++j){}
        if(j == what_size)
        {
            result = i;
            return true;
        }
    }

    return false;
}

lazy_string& lazy::operator+=(lazy_string& lhs, lazy_string const& rhs)
{
    lhs = concat(lhs, rhs);
    return lhs;
}

lazy_string lazy::operator+(lazy_string const& lhs, lazy_string const& rhs)
{
    return concat(lhs, rhs);
}

bool lazy::operator<(lazy_string const& lhs, lazy_string const& rhs)
{
    if(lhs.get_size() > rhs.get_size())
    {
        return false;
    }

    auto min_size =lhs.get_size();
    size_t i;
    for (i = 0; i < min_size && lhs.get_at(i) <= rhs.get_at(i); ++i)
    {
        if(lhs.get_at(i) < rhs.get_at(i))
        {
            return true;
        }
    }

    return false;
}

std::ostream& lazy::operator<<(std::ostream& os, lazy_string const& ls)
{
    print(os, ls);
    return os;
}

void lazy::print(std::ostream& os, lazy_string const& str)
{
    os << str.buffer_->get_data() << std::endl;
}

lazy_string lazy::concat(lazy_string const& str1, lazy_string const& str2)
{
    auto new_size = str1.get_size() + str2.get_size();
    auto new_buffer = new char[new_size + 1];
    strcpy(&new_buffer[0], str1.buffer_->get_data());
    strcpy(&new_buffer[str1.get_size() - 1], str2.buffer_->get_data());
    new_buffer[new_size] = '\0';
    lazy_string new_str(new_buffer);
    return new_str;
}

