#include "bits.h"
#include <cassert>
#include <algorithm>

helpers::bits::bit_modifier::bit_modifier(bits& bits, size_t const index)
    : array_(bits)
    , index_(index)
{}

helpers::bits::bits(size_t size)
    : size_(size)
    , content_(new bits_buffer(size))
{}

helpers::bits::bits(bits const& other)
    : size_(other.size_)
    , content_(new bits_buffer(*other.content_))
{}

helpers::bits::bits(bits && other)
    : size_(other.size_)
    , content_(new bits_buffer(*other.content_))
{
}

helpers::bits& helpers::bits::operator=(bits const& other)
{
    *content_ = *other.content_;
    return *this;
}

helpers::bits::~bits()
{
    delete content_;
}

void helpers::bits::resize(size_t size)
{
    if (size_ >= size) return;
    size_ = size;
    content_->resize(size);
}

uint32_t const& helpers::bits::operator[](size_t index) const
{
    return content_->get_data()[index];
}

helpers::bits::bit_modifier helpers::bits::operator[](size_t index)
{
    return bit_modifier(*this, index);
}

void helpers::bits::push_back(uint32_t value)
{
    if(content_->get_links_count() > 1)
    {
        content_->dup();
    }

    if(size_ >= content_->get_size())
    {
        content_->resize(2 * content_->get_size());
    }

    content_->get_data()[size_++] = value;
}

uint32_t& helpers::bits::pop_back()
{
    assert(size_ > 0);
    return content_->get_data()[--size_];
}

uint32_t const& helpers::bits::back() const
{
    assert(size_ > 0);
    return content_->get_data()[size_ - 1];
}

size_t helpers::bits::size() const
{
    return size_;
}

uint32_t helpers::bits::get_at(uint32_t index) const
{
    assert(index >= 0 && index < size_);
    return content_->get_data()[index];
}

void helpers::bits::set_at(size_t index, uint32_t value) const
{
    assert(index >= 0 && index < size_);
    if (content_->get_data()[index] == value) return;
    if (content_->get_links_count() > 1)
    {
        content_->dup();
    }

    content_->get_data()[index] = value;
}

int helpers::cmp_bits(bits const& lhs, bits const& rhs)
{
    int l_size = lhs.size();
    int r_size = rhs.size();
    auto max_size = std::max(l_size, r_size);
    for (auto i = max_size - 1; i >= 0; --i)
    {
        if (i < l_size && i >= r_size)
        {
            if (lhs[i] > 0)
            {
                return -1;
            }
        }

        if (i < r_size && i >= l_size)
        {
            if (rhs[i] > 0)
            {
                return 1;
            }
        }

        if (lhs[i] != rhs[i])
        {
            return lhs[i] < rhs[i] ? 1 : -1;
        }
    }

    return 0;
}


helpers::bits::bit_modifier& helpers::bits::bit_modifier::operator=(uint32_t value)
{
    array_.set_at(index_, value);
    return *this;
}

helpers::bits::bit_modifier::operator uint32_t() const
{
    return array_.get_at(index_);
}
