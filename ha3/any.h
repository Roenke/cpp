#pragma once
#include <exception>
#include <memory>
#include <string>

namespace utils
{
    class any
    {
        struct inner_base
        {
            using ptr = std::unique_ptr<inner_base>;
        };

        template<typename T>
        struct inner :inner_base {};
    public:
        any();

        template<typename T>
        any(T const&);

        any(any const&);

        template<typename T>
        any& operator=(T const&);
        any& operator=(any);
        friend void swap(any& l, any& r);

        bool empty() const;
    private:
        inner_base::ptr inner_;
    };

    template <typename T>
    any::any(T const& source)
        : inner_(new inner<T>(std::forward(source)))
    {}

    template <typename T>
    any& any::operator=(T const& other)
    {
        any res(other);
        swap(*this, res);
        return *this;
    }

    class bad_any_cast
        : public std::logic_error
    {
        explicit bad_any_cast(std::string const& what)
            : logic_error(what) {};
    };

    template<typename T>
    T any_cast(any const&);

    template<typename T>
    T* any_cast(any*);
}; /* utils */

template<typename T>
T utils::any_cast(any const& any)
{
    // TODO: if cast id imposible, throw bad_any_cast exception, else cast to T
    auto result = new T[1];
    return *result;
}

template <typename T>
T* utils::any_cast(any* any_ptr)
{
    // TODO: if cast id imposible, throw bad_any_cast exception, else cast to T
    auto result = new T[1];
    return result;
}

inline void utils::swap(any& l, any& r)
{
    std::swap(l.inner_, r.inner_);
}
