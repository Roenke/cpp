#pragma once
#include "shared_buffer.h"

class lazy_string
{
public:
    explicit lazy_string(const char *src);
    lazy_string(const lazy_string& src);

    bool empty() const;
    size_t get_size() const;

    char get_at(size_t ix) const;

private:
    shared_buffer buffer_;
};
