#pragma once
#include "shared_buffer.h"
#include <ostream>

namespace lazy
{
    class lazy_string
    {
    public:
        explicit lazy_string(const char *src);
        lazy_string(const lazy_string& src);
        lazy_string operator=(lazy_string src);
        void set_at(size_t ix, char value);

        bool empty() const;
        size_t get_size() const;

        char get_at(size_t ix) const;

    private:
        friend void print(std::ostream& os, lazy_string const& str);
        friend lazy_string concat(lazy_string const& str1, lazy_string const& str2);

        shared_buffer* buffer_;
    };

    bool find(lazy_string const&, const char*, size_t&, size_t ix=0);

    std::ostream& operator<<(std::ostream& os, lazy_string const& ls);
}; /* lazy */


