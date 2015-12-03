#pragma once
#include <iostream>

template <typename T>
void fill(T* begin, T* end, T value)
{
    while (begin < end)
    {
        *begin = value;
        ++begin;
    }
}
template <typename T>
void print(T* begin, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << begin[i] << " ";
    }
    std::cout << std::endl;
}
template<typename T>
void generate(T* begin, T* end, T(*gen)(void))
{
    while (begin < end)
    {
        *begin = gen();
        ++begin;
    }
}
template<typename T>
void copy(T* begin_source, T* end_source, T* begin_dest)
{
    while (begin_source < end_source)
    {
        *begin_dest = *begin_source;
        ++begin_source;
        ++begin_dest;
    }
}
template<typename T>
void for_each(T* begin, T* end, T(*functor)(T))
{
    while (begin < end)
    {
        *begin = functor(*begin);
        ++begin;
    }
}
template<typename T>
T accumulate(T* begin, T* end, T(*acc_fun)(T, T))
{
    if (begin < end - 1)
    {
        return acc_fun(*begin, accumulate(begin + 1, end, acc_fun));
    }

    return *begin;
}