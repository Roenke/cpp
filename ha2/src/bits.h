#pragma once
#include <cstdint>
#include "bits_buffer.h"

namespace helpers
{
    struct bits
    {
    private:
        struct bit_modifier
        {
            bit_modifier& operator=(uint32_t value);
            operator uint32_t() const;
            friend bits;
        private:
            bit_modifier(bits& bits, size_t const index);
            bits& array_;
            size_t index_;
        };
    public:
        bits() = delete;
        explicit bits(size_t);
        bits(bits const & other);
        bits(bits &&);
        bits& operator=(bits const & other);
        ~bits();

        void resize(size_t);

        uint32_t const& operator[](size_t) const;
        bit_modifier operator[](size_t);

        void push_back(uint32_t);
        uint32_t& pop_back();
        uint32_t const& back() const;

        size_t size() const;

    private:
        uint32_t get_at(uint32_t) const;
        void set_at(size_t, uint32_t) const;
        size_t size_;
        bits_buffer* content_;
    };
    int cmp_bits(bits const & lhs, bits const & rhs);
}; /* helpers */
