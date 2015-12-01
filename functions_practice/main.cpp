#include <vector>
#include <cassert>
#include <iostream>
#include "io.h"
void for_each(std::vector<int>& vector, int (*func)(int))
{
    auto size = vector.size();
    for (size_t i = 0; i < size; ++i)
    {
        vector[i] = func(vector[i]);
    }
}

long long sum_vector(std::vector<int> const& vector, int(*transform)(int))
{
    long long result = 0;
    auto size = vector.size();
    for (size_t i = 0; i < size; ++i)
    {
        result += transform(vector[i]);
    }

    return result;
}

int sqr_func(int arg)
{
    return arg * arg;
}

int sqrt_func(int arg)
{
    return static_cast<int>(sqrt(arg));
}

int identity(int arg)
{
    return arg;
}

void for_each_tests()
{
    std::vector<int> v1(10);
    v1.assign(10, 3);
    for_each(v1, sqr_func);
    assert(v1[0] == 9);
    assert(v1[9] == 9);

    for_each(v1, sqrt_func);
    assert(v1[0] == 3);
    assert(v1[9] == 3);

    std::cout << "for_each tests passed" << std::endl;
}

void sum_vector_tests()
{
    std::vector<int> v1(10);
    v1.assign(10, 3);

    auto result = sum_vector(v1, identity);
    assert(v1[0] == 3);
    assert(result == 10 * 3);

    result = sum_vector(v1, sqr_func);
    assert(result == 9 * 10);
    assert(v1[0] == 3);

    std::cout << "sum_vector tests passed" << std::endl;
}

void io_tests()
{
    FILE *f;
    fopen_s(&f, "in.txt", "r");
    uint64_t llvalue;
    double dvalue;
    int ivalue;
    char svalue[10];

    read(f, llvalue);
    read(f, dvalue);
    read(f, ivalue);
    //read(f, svalue);

    assert(llvalue == 10);
    assert(dvalue == 1000.);
    assert(ivalue == 123);
    //assert(svalue[0] == 'a');
    fclose(f);

    fopen_s(&f, "out.txt", "w");
    write(f, llvalue);
    write(f, dvalue);
    write(f, ivalue);
    //write(f, svalue);
    fclose(f);

    std::cout << "reads/writes tests passed" << std::endl;
}

int main()
{
    for_each_tests();

    sum_vector_tests();

    io_tests();
}
