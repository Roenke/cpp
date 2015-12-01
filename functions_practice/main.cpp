#include <vector>
#include <cassert>
#include <iostream>

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

int main()
{
    for_each_tests();
}
