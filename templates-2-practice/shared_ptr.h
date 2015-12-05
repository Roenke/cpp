#pragma once
namespace my_ptrs
{
    template<typename T>
    class shared_ptr
    {
    public:
        shared_ptr(T*);
        shared_ptr(shared_ptr const&);
        shared_ptr(shared_ptr&&);
        ~shared_ptr();

        operator bool();

        T* operator->();
        T& operator*();

        T* get();

        shared_ptr& operator=(shared_ptr other);
    private:
        size_t* count_;
        T* ptr_;
    };
}; /* my_ptrs */

template <typename T>
my_ptrs::shared_ptr<T>::shared_ptr(T* ptr)
    : count_(new size_t(1))
    , ptr_(ptr)
{}

template <typename T>
my_ptrs::shared_ptr<T>::shared_ptr(shared_ptr const& other)
    : count_(other.count_)
    , ptr_(other.ptr_)
{
    ++*count_;
}

template <typename T>
my_ptrs::shared_ptr<T>::shared_ptr(shared_ptr&& other)
    : count_(nullptr)
    , ptr_(nullptr)
{
    std::swap(count_, other.count_);
    std::swap(ptr_, other.ptr_);
}

template <typename T>
my_ptrs::shared_ptr<T>::~shared_ptr()
{
    --*count_;
    if(*count_ == 0)
    {
        delete ptr_;
    }
}

template <typename T>
my_ptrs::shared_ptr<T>::operator bool()
{
    return ptr_ != nullptr;
}

template <typename T>
T* my_ptrs::shared_ptr<T>::operator->()
{
    return ptr_;
}

template <typename T>
T& my_ptrs::shared_ptr<T>::operator*()
{
    return *ptr_;
}

template <typename T>
T* my_ptrs::shared_ptr<T>::get()
{
    return ptr_;
}

template <typename T>
my_ptrs::shared_ptr<T>& my_ptrs::shared_ptr<T>::operator=(shared_ptr other)
{
    ptr_ = other.ptr_;
    count_ = other.count_;
    if(ptr_ != nullptr)
    {
        ++*count_;
    }

    return *this;
}
