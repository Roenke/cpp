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
    lint num1(1);
    lint num2(1000);
    lint num3("10000000000000000");
    lint num4("10000000000000001");
    assert(num1 + num2 == 1001);
    assert(num1 + num3 == num4);
    assert(num2 + num1 == 1001);
    assert((num3 + num2).to_string() == "10000000000001000");
    auto num5 = num3 + num4;
    assert(num5.to_string() == "20000000000000001");

    std::cout << "Sum tests passed" << std::endl;
}

void minus_tests()
{
    lint num1(1000);
    lint num2("3984759834570309328349759834754");
    lint num3("8934769679583758672945879243653248740723658749856747564248765783249834263428484275248754");

    assert((num1 - 1).to_string() == "999");
    assert(num1 - 0 == num1);
    assert((num2 - num1).to_string() == "3984759834570309328349759833754");
    auto big_result(num3 - num2);

    assert(big_result + num2 == num3);
    assert(big_result - 0 == big_result);
    auto zero(big_result - big_result);
    assert(zero == 0);
    assert((big_result - big_result).is_small());
    assert(big_result.to_string() == "8934769679583758672945879243653248740723658749856747564244781023415263954100134515414000");

    std::cout << "subtraction tests passed" << std::endl;
}

void mul_tests()
{
    lint num1(1);
    lint num2(0);
    lint num3(10000);
    lint num4("892374984372368436589379843");
    lint num5("93488762387648723784687732");

    assert(num1 * num2 == 0);
    assert(num1 * 1 == num1);
    assert(num3 * num3 == 100000000);
    assert(num4 * 0 == 0);
    assert((num5 * 0).is_small());
    assert((num5 * num4).to_string() == "83427032874670095973945907379893169476596773290186076");

    std::cout << "mult tests passed" << std::endl;
}

void div_tests()
{
    lint num1(1000);
    lint num2(500);

    assert(num1 / num2 == 2);
    assert(num2 / num1 == 0);

    lint num3("100000000000000000000000000000000000000000000");
    assert((num3 / num1).to_string() == "100000000000000000000000000000000000000000");
    assert(num2 / num3 == 0);

    num3 /= num3;
    assert(num3 == 1);
    assert(num3.is_small());

    lint result("93432687672");
    lint a("83479847573967384749837946456");
    lint b("893475823647893678");

    auto res = a / b;
    assert(res == result);
    assert(!(a / b).is_small());

    lint b2("8347984757923738474983794");
    lint res2("9999");
    assert(a / b2 == res2);

    std::cout << "Division tests passed" << std::endl;
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
    
    lint big(3000000000LL);

    assert(bil != big);
    assert(1 != big);
    assert(1 < big);
    assert(-big < big);
    assert(-big == lint("-3000000000"));
    assert(-1 != -bil);
    assert(1000000001 == bil);


    std::cout << "Compare tests passed" << std::endl;
}

void increment_tests()
{
    lint one(1);
    lint two(0);
    lint three(10);
    lint minimum(INT32_MIN);
    lint maximum(INT32_MAX);

    assert(minimum-- == INT32_MIN);
    assert(!minimum.is_small());
    assert(++minimum == INT32_MIN);
    assert(minimum.is_small());
    assert(two-- == 0);
    assert(--(--one) == two);
    assert(maximum++ == INT32_MAX);
    assert(!maximum.is_small());
    assert(maximum-- != INT32_MAX);
    assert(maximum == INT32_MAX);
    assert(maximum.is_small());

    std::cout << "Increment tests passed" << std::endl;
}

void decrement_tests()
{
    
}

void abs_tests()
{
    lint zero(0);
    lint positive_small(1000);
    lint negative_small(-1000);
    lint positive_big("38726823756438756");
    lint negative_big("-38726823756438756");

    assert(abs(zero) == 0);
    assert(abs(positive_small) >= 0);
    assert(abs(negative_big) >= 0);
    assert(abs(negative_small) >= 0);
    assert(abs(positive_big) >= 0);
    assert(abs(negative_big) == positive_big);
    assert(abs(negative_small) == positive_small);
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

    assert(lint("8934769679583758672945879243653248740723658749856747564248765783249834263428484275248754").to_string() ==
        "8934769679583758672945879243653248740723658749856747564248765783249834263428484275248754");
}

void start_my_tests()
{
    my_vector_tests();

    eq_cmp_tests();

    plus_tests();
    minus_tests();
    div_tests();
    cmp_tests();
    mul_tests();
    
    //increment_tests();
   decrement_tests(); 
    abs_tests();
    pow_tests();
    from_string_test();
    to_string_tests();
    casts_tests();
}
