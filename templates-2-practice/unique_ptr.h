
namespace my_ptrs
{
    template<typename T>
    class unique_ptr
    {
    public:
        unique_ptr(T*);

    private:
        T* ptr_;
    };
};
template <typename T>
my_ptrs::unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr)
{}
