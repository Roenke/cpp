#pragma once
#include <cassert>

template<typename T>
class vector
{
    class proxy
    {
    public:
        proxy(vector<T>& vector, size_t const index)
            : vector_(vector)
            , index_(index)
        {}

        T operator=(T value) {
            vector_.set_value(index_, value);
            return *this;
        }

        operator T() const
        {
            return vector_.get_value(index_);
        }
    private:
        vector<T>& vector_;
        size_t index_;
    };
public:
    explicit vector(int);
    vector(vector<T> const&);
    vector<T>& operator=(vector<T> const&);
    ~vector();

    proxy operator[](size_t);
    void set_value(size_t, T);
    T const& get_value(size_t) const;

    void resize(size_t);

    void push_back(T);
    T& pop_back();
    T const& back();
    size_t size() const;
private:
    size_t  size_;
    size_t  capacity_;
    size_t* link_count_;
    T* data_;
};


template <typename T>
vector<T>::vector(int size)
    : size_(size)
    , capacity_(size)
    , link_count_(new size_t(1))
    , data_(new T[size])
{}

template <typename T>
vector<T>::vector(vector<T> const& src)
    : size_(src.size_)
    , capacity_(src.capacity_)
    , link_count_(src.link_count_)
    , data_(src.data_)
{
    ++*link_count_;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T> const& src)
{
    if (data_ == src.data_) return *this;
    *--link_count_;
    if(*link_count_ == 0)
    {
        delete[] data_;
    }

    data_ = src.data_;
    link_count_ = src.link_count_;
    size_ = src.size_;
    capacity_ = src.capacity_;
    ++*link_count_;

    return *this;
}

template <typename T>
vector<T>::~vector()
{
    --*link_count_;
    if(*link_count_ == 0)
    {
        delete[] data_;
    }
}

template <typename T>
typename vector<T>::proxy vector<T>::operator[](size_t index)
{
    return proxy(*this, index);
}

template <typename T>
void vector<T>::set_value(size_t index, T value)
{
    if(*link_count_ > 1)
    {
        --*link_count_;
        auto new_buf = new T[capacity_];
        link_count_ = new size_t(1);
        for (int i = 0; i < size_; ++i)
        {
            new_buf[i] = data_[i];
        }
        data_ = new_buf;
    }
    
    assert(index >= 0 && index < size_);
    data_[index] = value;
}

template <typename T>
T const& vector<T>::get_value(size_t index) const
{
    assert(index >= 0 && index < size_);
    return data_[index];
}

template <typename T>
void vector<T>::resize(size_t size)
{
    if (size <= size_) 
    {
        size_ = size;
        return;
    }

    assert(size_ < size);
    --*link_count_;
    auto new_buf = new T[size];
    for (int i = 0; i < size_; ++i)
    {
        new_buf[i] = data_[i];
    }
    size_ = size;
    capacity_ = size_;
    if(*link_count_ == 0)
    {
        delete[] data_;
    }
    data_ = new_buf;
    *link_count_ = 1;
}

template <typename T>
void vector<T>::push_back(T value)
{
    if(*link_count_ > 1)
    {
        --*link_count_;
        auto new_buf = new T[capacity_];
        link_count_ = new size_t(1);
        for (int i = 0; i < size_; ++i)
        {
            new_buf[i] = data_[i];
        }
        data_ = new_buf;
    }

    assert(*link_count_ == 1);
    if(size_ >= capacity_)
    {
        capacity_ *= 2;
        auto new_buf = new T[capacity_];
        for (int i = 0; i < size_; ++i)
        {
            new_buf[i] = data_[i];
        }
        data_ = new_buf;
    }

    data_[size_++] = value;
}

template <typename T>
T& vector<T>::pop_back()
{
    if (*link_count_ > 1)
    {
        --*link_count_;
        auto new_buf = new T[capacity_];
        link_count_ = new size_t(1);
        for (int i = 0; i < size_; ++i)
        {
            new_buf[i] = data_[i];
        }
        data_ = new_buf;
    }

    assert(*link_count_ == 1);
    assert(size_ >= 1);
    return data_[--size_];
}

template <typename T>
T const& vector<T>::back()
{
    assert(size_ > 0);
    return data_[size_ - 1];
}

template <typename T>
size_t vector<T>::size() const
{
    return size_;
}
