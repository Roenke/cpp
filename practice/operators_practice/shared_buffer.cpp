#include "shared_buffer.h"
#include <memory>
using namespace lazy;

shared_buffer::shared_buffer(size_t size)
    : ptrs_count_(new int(1))
    , data_size_(new int(size))
    , data_(new char[size])
{
}

shared_buffer::shared_buffer(const shared_buffer& src)
    : ptrs_count_(src.ptrs_count_)
    , data_size_(src.data_size_)
    , data_(src.data_)
{
    ++(*ptrs_count_);
}

shared_buffer& shared_buffer::operator=(shared_buffer other)
{
    if(data_ != nullptr)
    {
        std::swap(*this, other);
    }

    return *this;
}

shared_buffer::~shared_buffer()
{
    if (data_ != nullptr)
    {
        --*ptrs_count_;
        if (*ptrs_count_ == 0)
        {
            delete[] data_;
            delete ptrs_count_;
        }

        data_ = nullptr;
        ptrs_count_ = nullptr;
    }
}

char* shared_buffer::get_data()
{
    return data_;
}

const char* shared_buffer::get_data() const
{
    return data_;
}

size_t shared_buffer::get_size() const
{
    if(data_size_ == nullptr)
    {
        return 0;
    }

    return *data_size_;
}

