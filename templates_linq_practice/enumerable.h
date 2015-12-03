#pragma once
#include <vector>
#include <functional>
#include <type_traits>

namespace linq
{
    template<typename T>
    class enumerable
    {
    public:
        enumerable(std::vector<T> const&);
        enumerable<T> where(std::function<bool(T)>);

        template<typename Fn, typename U = typename std::result_of<Fn(T)>::type>
        enumerable<U> select(Fn && f);

        size_t count(std::function<bool(T)>);
        size_t count();

        bool any();
        bool any(std::function<bool(T)>);

        std::vector<T> to_vector();

    private:
        std::vector<T> internal_;
    };

    template<typename T>
    enumerable<T> from(std::vector<T> const& vector);
}; /* linq */



template <typename T>
linq::enumerable<T>::enumerable(std::vector<T> const& other)
    : internal_(other)
{}

template <typename T>
linq::enumerable<T> linq::enumerable<T>::where(std::function<bool(T)> predicate)
{
    std::vector<T> result;
    for(auto const& elem: internal_)
    {
        if (predicate(elem))
        {
            result.push_back(elem);
        }
    }

    return enumerable(result);
}

template <typename T>
template <typename Fn, typename U>
linq::enumerable<U> linq::enumerable<T>::select(Fn&& f)
{
    std::vector<U> result;
    for (auto const& elem : internal_)
    {
        result.push_back(f(elem));
    }

    return enumerable<U>(result);
}

template <typename T>
size_t linq::enumerable<T>::count(std::function<bool(T)> predicate)
{
    size_t result = 0;
    for(auto const& elem:internal_)
    {
        if(predicate(elem))
        {
            ++result;
        }
    }

    return result;
}

template <typename T>
size_t linq::enumerable<T>::count()
{
    return internal_.size();
}

template <typename T>
bool linq::enumerable<T>::any()
{
    return internal_.size() != 0;
}

template <typename T>
bool linq::enumerable<T>::any(std::function<bool(T)> predicate)
{
    for(auto const& elem:internal_)
    {
        if(predicate(elem))
        {
            return true;
        }
    }

    return false;
}

template <typename T>
std::vector<T> linq::enumerable<T>::to_vector()
{
    return internal_;
}

template <typename T>
linq::enumerable<T> linq::from(std::vector<T> const& vector)
{
    enumerable<T> value(vector);
    return value;
}
