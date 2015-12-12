#include "bits_buffer.h"
#include <algorithm>

helpers::bits_buffer::bits_buffer(size_t size)
    : size_(std::max(size, 1U))
    , links_count_(new size_t(1))
    , data_(new uint32_t[size_])
{
    fill();
}

helpers::bits_buffer::bits_buffer(bits_buffer const& other)
    : size_(other.size_)
    , links_count_(other.links_count_)
    , data_(other.data_)
{
    ++*links_count_;
}

helpers::bits_buffer& helpers::bits_buffer::operator=(bits_buffer const& other)
{
    size_ = other.size_;
    data_ = other.data_;
    links_count_ = other.links_count_;
    ++*links_count_;

    return *this;
}

helpers::bits_buffer::~bits_buffer()
{
    unlink();
    if(*links_count_ == 0)
    {
        delete[] data_;
        delete links_count_;
    }
}

void helpers::bits_buffer::resize(size_t new_size)
{
    unlink();

    auto new_buf = new uint32_t[new_size];
    for (size_t i = 0; i < new_size; ++i)
    {
        new_buf[i] = i < size_ ? data_[i] : 0;
    }

    if(*links_count_ == 0)
    {
        delete[] data_;
        delete links_count_;
    }

    size_ = new_size;
    links_count_ = new size_t(1);
    data_ = new_buf;
}

uint32_t* helpers::bits_buffer::get_data() const
{
    return data_;
}

size_t helpers::bits_buffer::get_size() const
{
    return size_;
}

size_t helpers::bits_buffer::get_links_count() const
{
    return *links_count_;
}

void helpers::bits_buffer::dup()
{
    if (*links_count_ == 1) return;
    unlink();
    links_count_ = new size_t(1);
    auto new_data = new uint32_t[size_];
    for (size_t i = 0; i < size_; ++i)
    {
        new_data[i] = data_[i];
    }

    data_ = new_data;
}

void helpers::bits_buffer::unlink()
{
    *--links_count_;
}

void helpers::bits_buffer::fill() const
{
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = 0;
    }
}
