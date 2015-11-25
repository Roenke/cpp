#include "lint.h"
#include "mytests.h"
#include "vector.h"
#include <cassert>
#include <iostream>

using namespace apa;
using helpers::vector;

void casts_tests()
{
    auto ll_number = 1000000000000;
    lint my_long(ll_number);
    auto new_ll = static_cast<long long>(my_long);
    assert(ll_number == new_ll);

    long long short_long = 100000;
    lint my(short_long);
    assert(my.is_small());

    long long min_int = INT32_MIN;
    long long max_int = INT32_MAX;
    auto max_int_overflow = INT32_MAX + 1LL;
    auto min_int_overflow = INT32_MIN - 1LL;
    lint my_big(max_int);
    lint my_small(min_int);
    lint my_big_overflow(max_int_overflow);
    lint my_small_overflow(min_int_overflow);

    assert(my_big.is_small());
    assert(my_small.is_small());
    assert(!my_big_overflow.is_small());
    assert(!my_small_overflow.is_small());

    assert(max_int == my_big);
    assert(my_small_overflow == min_int_overflow);

    std::cout << "Long long casts passed" << std::endl;
}

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

void eq_cmp_tests()
{
    lint num1(123);
    lint num2(-123);
    lint num3(123.);

    assert(num1 != num2);
    assert(-num1 == num2);
    assert(num1 == -num2);
    assert(num1 == num3);

    lint big_num1(1233546546546LL);
    lint big_num2("3495756795867895670384546");
    lint big_num3("-3495756795867895670384546");

    assert(big_num2 != big_num3);
    assert(big_num2 == -big_num3);
    assert(-big_num2 == big_num3);
    assert(num1 != big_num1);
    assert(num2 != big_num3);
}

void cmp_tests()
{
    lint num1(123);
    lint num3(1324);
    lint num2("38457984573489057349857439876");

    assert(num1 == num1);

    assert(num1 < num3);
    assert(num3 >= num1);
    assert(num3 > num1);
    assert(num1 <= num3);
    assert(num1 != num3);

    assert(num1 < num2);
    assert(num1 <= num2);
    assert(num2 >= num1);
    assert(!(num2 < num2));
    assert(num2 <= num2);

    lint bil(1000000001);

    assert(bil > 1);
    assert(1 < bil);
    assert(bil >= 1);
    assert(bil > num1);
    assert(bil < num2);
    assert(num2 >= bil);

    auto neg_bil(-bil);
    assert(bil == -neg_bil);
    assert(-(-neg_bil) == neg_bil);
    assert(bil != -bil);
    assert(bil > neg_bil);

    std::cout << "Compare tests passed" << std::endl;
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
    assert(num1.is_small());

    lint num2("123235");
    assert(num2.is_small());

    lint num3("1000000000");
    assert(!num3.is_small());

    lint num4("10000000010");
    lint num5("999999999");
    lint num6("-1");
    lint num7("-0000000000000000000000000000000000000000000000000000000000001");
    lint num8("0000000000000000000000000000000000000000000000000000000000001");
    lint num9("+0000000000000000000000000000000000000000000000000000000000001");
    lint num10("-999999999");
    //auto result = num1 + 2 * num2 + 3 * num3 + 4 * num4;
    //assert(lint("6012569909") == result - num5);

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

    vector1.push_back(1);
    vector1.push_back(2);
    vector1.push_back(3);
    vector1.push_back(4);
    vector1.push_back(5);

    std::cout << "vector tests passed" << std::endl;
}

void to_string_tests()
{
    lint num1(100);
    auto str1 = num1.to_string();
    assert(str1 == "100");

    lint num2(-100);
    auto str2 = num2.to_string();
    assert(str2 == "-100");

    lint num3("+34554654897934534543534");
    auto str3 = num3.to_string();
    assert(str3 == "34554654897934534543534");

    lint num4("-34554654897934534543534");
    auto str4 = num4.to_string();
    assert(str4 == "-34554654897934534543534");
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
    from_string_test();
    to_string_tests();
    casts_tests();
    eq_cmp_tests();
}
