/*#include <iostream>

template <typename T>
void fill(T* begin, T* end, T value)
{
    while(begin < end)
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
void generate(T* begin, T* end, T (*gen)(void))
{
    while(begin < end)
    {
        *begin = gen();
        ++begin;
    }
}

template<typename T>
void copy(T* begin_source, T* end_source, T* begin_dest)
{
    while(begin_source < end_source)
    {
        *begin_dest = *begin_source;
        ++begin_source;
        ++begin_dest;
    }
}

template<typename T>
void for_each(T* begin, T* end, T (*functor)(T))
{
    while(begin < end)
    {
        *begin = functor(*begin);
        ++begin;
    }
}

template<typename T>
T accumulate(T* begin, T* end, T (*acc_fun)(T, T))
{
    if(begin < end - 1)
    {
        return acc_fun(*begin, accumulate(begin + 1, end, acc_fun));
    }
    
    return *begin;
}

int generator()
{
    static auto i = 10;
    return i++;
}

double double_generator()
{
    static auto i = 1.;
    return i++;
}

double sqr_functor(double arg)
{
    return arg * arg;
}

double sum_double_acc(double a, double b)
{
    return a + b;
}

void main()
{
    auto int_array = new int[10];
    fill(&int_array[0], &int_array[5], 0);
    fill(&int_array[5], &int_array[10], 5);
    print(int_array, 10);

    auto gen_int_array = new int[10];
    generate(&gen_int_array[0], &gen_int_array[10], generator);
    print(gen_int_array, 10);

    auto dest = new int[10];
    copy(&int_array[0], &int_array[10], dest);

    std::cout << "copy result: ";
    print(dest, 10);

    auto double_arr = new double[10];
    fill(&double_arr[0], &double_arr[10], 0.);
    generate(&double_arr[0], &double_arr[10], double_generator);
    for_each(&double_arr[0], &double_arr[10], sqr_functor);
    print(double_arr, 10);

    std::cout << "prev array sum: " << accumulate(&double_arr[0], &double_arr[10], sum_double_acc) << std::endl;
}*/