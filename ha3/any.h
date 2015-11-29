#pragma once
#include <exception>
#include <memory>
#include <string>

namespace utils
{
    class any
    {
    public:
        any();

        template<typename T>
        explicit any(T const&);

        template<typename T>
        any& operator=(T const&);

        struct inner_base
        {
            using ptr = std::unique_ptr<inner_base>;
        };

        template<typename T>
        struct inner :inner_base {};


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
        inner_ = std::make_unique<inner<T>>(std::forward<T>(other));
        return *this;
    }

    class bad_any_cast
        : public std::runtime_error
    {
        explicit bad_any_cast(std::string const& what)
            : runtime_error(what) {};
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
