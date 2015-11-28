#pragma once
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

        bool empty() const;
    };

    inline any::any()
    {
    }

    inline bool any::empty() const
    {
        return false;
    }

    template <typename T>
    any::any(T const&)
    {
    }

    template <typename T>
    any& any::operator=(T const&)
    {
        any result;
        return result;
    }

    class bad_any_cast
        : public std::exception
    {
        
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
