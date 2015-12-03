#include "enumerable.h"
#include <cassert>
#include <iostream>

void enumerable_tests()
{
    std::vector<int> v1 = { 10,20,30,40,50 };
    auto res = linq::from(v1).where([](int x) {return x <= 30; }).to_vector();
    assert(res.size() == 3);
    assert(res[2] == 30);

    std::cout << "from / where / to_vector tests passed" << std::endl;
}

void select_tests()
{
    std::vector<int> v1 = { 1,2,3,4,5,6,7,8 };
    std::vector<double> v2 = { 1., 4., 9., 16. };

    auto result = linq::from(v1)
        .where([](int x) {return x < 5; })
        .select<double>([](int x) { return static_cast<double>(x) * x; } )
        .to_vector();

    assert(result.size() == 4);
    
    for (auto i = 0; i < result.size(); ++i)
    {
        assert(result[i] == v2[i]);
    }

    std::cout << "select tests passed" << std::endl;
}

void count_tests()
{
    std::vector<int> v1 = { 1,2,3,4,5,6,7,8 };
    auto enumerable = linq::from(v1);

    assert(enumerable.count() == 8);
    auto even = enumerable.count([](int x) { return x % 2 == 0; });
    assert(even == 4);

    std::cout << "count tests passed" << std::endl;
}

void any_tests()
{
    std::vector<double> empty;
    std::vector<int> v1 = { 1,2,3,4,5,6,7,8 };
    auto enumerable = linq::from(v1);

    assert(linq::from(empty).any() == false);

    assert(enumerable.any() == true);
    assert(enumerable.any([](int x) {return x % 2 == 0; }) == true);
    assert(enumerable.any([](int x) {return x > 8; }) == false);

    std::cout << "any tests passed" << std::endl;
}

int main()
{
    enumerable_tests();

    select_tests();

    count_tests();

    any_tests();
}
