#pragma once
#include <cstdint>
#include <cassert>

namespace helpers
{
    template<typename T>
    class vector
    {
    public:
        vector();
        explicit vector(int);
        vector(vector<T> const&);
        vector<T>& operator=(vector<T> const&);

        T& operator[](int);
        
        void push_back(T);
        T& pop_back();
        size_t size() const;

    private:
        uint32_t size_;
        uint32_t capacity_;
        
        T* content_;

        void allocate(size_t new_capacity = -1);
    };

    template<typename T>
    bool operator==(vector<T> const&, vector<T> const&);
    
}; /* helpers */

template <typename T>
helpers::vector<T>::vector()
    : size_(0)
    , capacity_(0)
    , content_(nullptr)
{}

template <typename T>
helpers::vector<T>::vector(int size)
    : size_(size)
    , capacity_(size)
    , content_(new T[size])
{
    memset(content_, 0, sizeof(T) * size);
}

template <typename T>
helpers::vector<T>::vector(vector<T> const& other)
    : size_(0)
    , capacity_(0)
{
    allocate(other.size());
    size_ = other.size();
    for (size_t i = 0; i < size_; ++i)
    {
        content_[i] = other.content_[i];
    }
}

template <typename T>
helpers::vector<T>& helpers::vector<T>::operator=(vector<T> const& other)
{
    size_ = other.size_;
    allocate(other.size_);
    for (size_t i = 0; i < other.size_; ++i)
    {
        content_[i] = other.content_[i];
    }

    return *this;
}

template <typename T>
T& helpers::vector<T>::operator[](int index)
{
    return content_[index];
}

template <typename T>
void helpers::vector<T>::push_back(T elem)
{
    if (size_ == capacity_)
    {
        allocate();
    }

    content_[size_++] = elem;
}

template <typename T>
T& helpers::vector<T>::pop_back()
{
    assert(size_ > 0);
    return content_[--size_];
}

template <typename T>
size_t helpers::vector<T>::size() const
{
    return size_;
}

template <typename T>
void helpers::vector<T>::allocate(size_t capacity = -1)
{
    if (capacity == -1)
    {
        capacity = capacity_ == 0 ? 2 : capacity_ * 2;
    }

    assert(capacity >= size_);

    auto memory_region = new T[capacity];
    memset(memory_region, 0, sizeof(T) * capacity);
    for (size_t i = 0; i < size_; ++i)
    {
        memory_region[i] = content_[i];
    }

    if(content_!= nullptr)
        delete[] content_;

    content_ = memory_region;
    capacity_ = capacity;
}

template <typename T>
bool helpers::operator==(vector<T> const& l, vector<T> const& r)
{
    {
        if (l.size() != r.size())
        {
            return false;
        }

        auto size = l.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (l[i] != r[i])
            {
                return false;
            }
        }

        return true;
    }
}

