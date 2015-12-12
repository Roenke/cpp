#pragma once
#include <cstdint>
#include <cstddef>

namespace helpers
{
    struct bits_buffer
    {
        bits_buffer() = delete;
        explicit bits_buffer(size_t);
        bits_buffer(bits_buffer const&);
        bits_buffer(bits_buffer &&);
        bits_buffer& operator=(bits_buffer const & other);
        ~bits_buffer();

        void resize(size_t);
        uint32_t* get_data() const;

        size_t get_size() const;
        size_t get_links_count() const;

        void dup();
    private:
        size_t size_;
        size_t* links_count_;
        uint32_t* data_;

        void unlink() const;
        void fill() const;
    };
}; /*helpers */

