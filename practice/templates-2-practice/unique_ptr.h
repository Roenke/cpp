
namespace my_ptrs
{
    template<typename T>
    class unique_ptr
    {
    public:
        unique_ptr(T*);
        unique_ptr(unique_ptr &&);
        unique_ptr& operator=(unique_ptr&&);
        T* operator->();

        operator bool();

        T& operator*();

        T* get();

        ~unique_ptr();
    private:
        void free();
        T* ptr_;
    };
};
template <typename T>
my_ptrs::unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr)
{}

template <typename T>
my_ptrs::unique_ptr<T>::unique_ptr(unique_ptr&& other)
{
    std::swap(ptr_, other.ptr_);
}

template <typename T>
my_ptrs::unique_ptr<T>& my_ptrs::unique_ptr<T>::operator=(unique_ptr&& other)
{
    std::swap(ptr_, other.ptr_);
    return *this;
}

template <typename T>
T* my_ptrs::unique_ptr<T>::operator->()
{
    if (ptr_ == nullptr)
    {
        throw npe_exception();
    }

    return ptr_;
}

template <typename T>
my_ptrs::unique_ptr<T>::operator bool()
{
    return ptr_ != nullptr;
}

template <typename T>
T& my_ptrs::unique_ptr<T>::operator*()
{
    if (ptr_ == nullptr)
    {
        throw npe_exception();
    }

    return *ptr_;
}

template <typename T>
T* my_ptrs::unique_ptr<T>::get()
{
    if (ptr_ == nullptr)
    {
        throw npe_exception();
    }

    return ptr_;
}

template <typename T>
my_ptrs::unique_ptr<T>::~unique_ptr()
{
    free();
}

template <typename T>
void my_ptrs::unique_ptr<T>::free()
{
    if (ptr_ != nullptr)
    {
        std::cerr << "Unique poiner. Delete object foo at " << ptr_ << std::endl;
    }

    delete ptr_;
}
