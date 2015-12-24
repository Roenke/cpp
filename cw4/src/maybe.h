#include <cstdint>
#include <memory>
#include <stdexcept>
#include <new>

namespace utils
{
    class empty_class {};

    const empty_class empty = empty_class();

    class maybe_exception
        : public std::runtime_error
    {
    public:
        maybe_exception()
            : runtime_error("Maybe is empty")
        {
        }
    };

    template<typename T>
    class maybe
    {
    public:
        maybe();
        maybe(T const&);
        maybe(empty_class);
        maybe(maybe const&);
        ~maybe();

        maybe& operator=(T const&);
        maybe& operator=(empty_class const&);

        T* operator->();
        T const* operator->() const;

        T& operator*();
        T const& operator*() const;

        T& get();
        T const& get() const;

        explicit operator bool() const;
        bool operator!() const;

    private:
        void fill_zero();
        T* ptr();
        T const* ptr() const;

        char object_[sizeof(T)];

        bool is_empty_;
    };

    template <typename T>
    maybe<T>::maybe()
    {
        fill_zero();

        is_empty_ = true;
    }

    template <typename T>
    maybe<T>::maybe(T const& value)
    {
        is_empty_ = false;
        new (object_) T(value);
    }

    template <typename T>
    maybe<T>::maybe(empty_class)
        : maybe()
    {}

    template <typename T>
    maybe<T>::maybe(maybe const& other)
    {
        is_empty_ = other.is_empty_;

        if (is_empty_)
        {
            fill_zero();
        }
        else
        {
            ptr()->~T();
            new (object_) T(other.object_);
        }
    }

    template <typename T>
    maybe<T>::~maybe()
    {
        if(!is_empty_)
        {
            ptr()->~T();
        }
    }

    template <typename T>
    maybe<T>& maybe<T>::operator=(T const& value)
    {
        new (object_) T(value);
        is_empty_ = false;

        return *this;
    }

    template <typename T>
    maybe<T>& maybe<T>::operator=(empty_class const&)
    {
        is_empty_ = true;
        fill_zero();

        return *this;
    }

    template <typename T>
    T* maybe<T>::operator->()
    {
        return ptr();
    }

    template <typename T>
    T const* maybe<T>::operator->() const
    {
        return ptr();
    }

    template <typename T>
    T& maybe<T>::operator*()
    {
        return *ptr();
    }

    template <typename T>
    T const& maybe<T>::operator*() const
    {
        return *ptr();
    }

    template <typename T>
    T& maybe<T>::get()
    {
        if (is_empty_)
        {
            throw maybe_exception();
        }

        return *(ptr());
    }

    template <typename T>
    T const& maybe<T>::get() const
    {
        if (is_empty_)
        {
            throw maybe_exception();
        }

        return *(ptr());
    }

    template <typename T>
    maybe<T>::operator bool() const
    {
        return !is_empty_;
    }

    template <typename T>
    bool maybe<T>::operator!() const
    {
        return is_empty_;
    }

    template <typename T>
    void maybe<T>::fill_zero()
    {
        for (size_t i = 0; i < sizeof(T); ++i)
        {
            object_[i] = 0;
        }
    }

    template <typename T>
    T* maybe<T>::ptr()
    {
        return reinterpret_cast<T*>(object_);
    }

    template <typename T>
    T const* maybe<T>::ptr() const
    {
        return reinterpret_cast<T const*>(object_);
    }
}
