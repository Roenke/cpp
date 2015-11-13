#include "lint.h"
#include "mytests.h"
#include "vector.h"
#include <cassert>
#include <iostream>

using namespace apa;
using helpers::vector;

void plus_tests()
{
    
}

void minus_tests()
{
    
}

void mul_tests()
{
    
}

void div_tests()
{
    
}

void cmp_tests()
{
    
}

void increment_tests()
{
    
}

void decrement_tests()
{
    
}

void abs_tests()
{
    
}

void pow_tests()
{
    
}

void from_string_test()
{
    lint num1("12323434");
    lint num2("123235");
    lint num3("1000000000");
    lint num4("1000000001");
    lint num5("999999999");
    auto result = num1 + 2 * num2 + 3 * num3 + 4 * num4;
    assert(lint("6012569909") == result - num5);

    std::cout << "from string tests passed" << std::endl;
}

void my_vector_tests()
{
    vector<int> vector1;
    vector<uint32_t> vector2(34);
    vector2[32] = 34;
    vector2[33] = 244;
    vector1.push_back(345);
    assert(vector1.size() == 1);
    assert(vector2[0] == 0);
    assert(vector2.pop_back() == 244);
    assert(vector2.size() == 33);

    auto vector3(vector2);
    assert(vector3.size() == vector2.size());
    auto vector4 = vector3;
    vector4[0] = 1;
    assert(vector4[0] != vector3[0]);

    std::cout << "vector tests passed" << std::endl;
}

void start_my_tests()
{
    my_vector_tests();

    plus_tests();
    minus_tests();
    mul_tests();
    div_tests();
    cmp_tests();
    increment_tests();
    decrement_tests(); 
    abs_tests();
    pow_tests();
    //from_string_test();
}
