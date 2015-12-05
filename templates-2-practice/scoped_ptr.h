
#include "npe_exception.h"

namespace my_ptrs
{
    template <typename T>
    class scoped_ptr 
    {
    public:
        scoped_ptr(T*);
        scoped_ptr(T const&) = delete;
        scoped_ptr& operator=(T const&) = delete;
        T* get();

        operator bool() const;

        void reset(T* = nullptr);

        T* operator->();
        T& operator*();

        ~scoped_ptr();
    private:
        void free();
        T* ptr_;
    };
}; /* my_ptrs */


template <typename T>
my_ptrs::scoped_ptr<T>::scoped_ptr(T* ptr)
    : ptr_(ptr)
{}

template <typename T>
T* my_ptrs::scoped_ptr<T>::get()
{
    return ptr_;
}

template <typename T>
my_ptrs::scoped_ptr<T>::operator bool() const
{
    return static_cast<bool>(ptr_);
}

template <typename T>
void my_ptrs::scoped_ptr<T>::reset(T* other)
{
    free();
    ptr_ = other;
}

template <typename T>
T* my_ptrs::scoped_ptr<T>::operator->()
{
    if (ptr_ == nullptr)
    {
        throw npe_exception();
    }

    return ptr_;
}

template <typename T>
T& my_ptrs::scoped_ptr<T>::operator*()
{
    if(ptr_ == nullptr)
    {
        throw npe_exception();
    }

    return *ptr_;
}

template <typename T>
my_ptrs::scoped_ptr<T>::~scoped_ptr()
{
    free();
}

template <typename T>
void my_ptrs::scoped_ptr<T>::free()
{
    if(ptr_ != nullptr)
    {
        std::cerr << "Delete object foo at " << ptr_ << std::endl;
    }

    delete ptr_;
}
