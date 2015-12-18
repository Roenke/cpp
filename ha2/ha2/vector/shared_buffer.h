#pragma once
#include <memory>

template<typename T>
class shared_buffer
{
public:
    explicit shared_buffer(size_t);
    shared_buffer(shared_buffer const & src);
    shared_buffer& operator=(shared_buffer src);
    ~shared_buffer();

    T* get_data();
    const T* get_data() const;
    size_t get_size() const;
private:
    size_t size_;
    size_t* link_count_;
    T* data_;
};

template <typename T>
shared_buffer<T>::shared_buffer(size_t size)
    : size_(size)
    , link_count_(new size_t(1))
    , data_(new T[size])
{}

template <typename T>
shared_buffer<T>::shared_buffer(shared_buffer const& src)
    : size_(src.size_)
    , link_count_(src.link_count_)
    , data_(src.data_)
{
    ++*link_count_;
}

template <typename T>
shared_buffer<T>& shared_buffer<T>::operator=(shared_buffer src)
{
    std::swap(*this, src);
    return *this;
}

template <typename T>
shared_buffer<T>::~shared_buffer()
{
    --*link_count_;
    if(*link_count_ == 0)
    {
        delete[] data_;
    }
}

template <typename T>
T* shared_buffer<T>::get_data()
{
    return data_;
}

template <typename T>
const T* shared_buffer<T>::get_data() const
{
    return data_;
}

template <typename T>
size_t shared_buffer<T>::get_size() const
{
    return size_;
}
