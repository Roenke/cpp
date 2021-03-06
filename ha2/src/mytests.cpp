#include "lint.h"
#include "mytests.h"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace apa;

void great_test()
{
    std::ifstream sum_file("sum.test");
    std::ifstream sub_file("sub.test");
    std::ifstream mul_file("mul.test");
    std::ifstream div_file("div.test");
    lint my_result;
    size_t successed = 0;
    int n = 0;
    sum_file >> n;
    std::cout << n << std::endl;
    lint a, b, result;
    for (int i = 1; i <= n; ++i)
    {
        sum_file >> a >> b >> result;
        try
        {
            my_result = a + b;
        }
        catch(std::exception const& e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
            continue;
        }
        if (my_result == result)
        {
            successed += 1;
        }
        else
        {
            std::cout << "Wrong answer test " << i << std::endl;
            std::cout << "a = " << a << std::endl;
            std::cout << "b = " << b << std::endl;
            std::cout << "res = " << result << std::endl;
            std::cout << "my res = " << my_result << std::endl;
        }
    }
    std::cout << "Sum tests result: " << successed << " / " << n << std::endl;

    successed = 0;
    mul_file >> n;
    for (int i = 1; i <= n; ++i)
    {
        mul_file >> a >> b >> result;
        my_result = a * b;
        if (my_result == result)
        {
            successed += 1;
        }
        else
        {
            std::cout << "Wrong answer test " << i << std::endl;
            std::cout << "a = " << a << std::endl;
            std::cout << "b = " << b << std::endl;
            std::cout << "res = " << result << std::endl;
            std::cout << "my res = " << my_result << std::endl;
        }
    }
    std::cout << "Mul tests result: " << successed << " / " << n << std::endl;

    successed = 0;
    sub_file >> n;
    for (int i = 1; i <= n; ++i)
    {
        sub_file >> a >> b >> result;
        my_result = a - b;
        if (my_result == result)
        {
            successed += 1;
        }
        else
        {
            std::cout << "Wrong answer test " << i << std::endl;
            std::cout << "a = " << a << std::endl;
            std::cout << "b = " << b << std::endl;
            std::cout << "res = " << result << std::endl;
            std::cout << "my res = " << my_result << std::endl;

        }
    }
    std::cout << "Sub tests result: " << successed << " / " << n << std::endl;

    successed = 0;
    div_file >> n;
    for (int i = 1; i <= n; ++i)
    {
        div_file >> a >> b >> result;
        try
        {
            my_result = a / b;
        }
        catch (std::exception const& e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
            continue;
        }
        if (my_result == result)
        {
            successed += 1;
        }
        else
        {
            std::cout << "Wrong answer test " << i << std::endl;
            std::cout << "a = " << a << std::endl;
            std::cout << "b = " << b << std::endl;
            std::cout << "res = " << result << std::endl;
            std::cout << "my res = " << my_result << std::endl;
        }
    }
    std::cout << "Div tests result: " << successed << " / " << n << std::endl;
}

void casts_tests()
{
    auto ll_number = 1000000000000LL;
    lint my_long(ll_number);
    assert(ll_number == static_cast<long long>(my_long));

    long long short_long = 100000;
    lint my(short_long);
    assert(my.is_small());

    long long min_int = -INT32_MAX;
    long long max_int = INT32_MAX;
    auto max_int_overflow = INT32_MAX + 1LL;
    auto min_int_overflow = -INT32_MAX - 1LL;
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

    assert(static_cast<int>(my_big) == INT32_MAX);
    assert(static_cast<int>(my_small_overflow) == INT32_MIN);

    std::cout << "Long long casts passed" << std::endl;
}

void plus_tests()
{
    lint num1(1);
    lint num2(1000);
    lint num3("10000000000000000");
    lint num4("10000000000000001");
    num3.to_string();
    assert(num1 + num2 == 1001);
    assert(num1 + num3 == num4);
    assert(num2 + num1 == 1001);
    assert((num3 + num2).to_string() == "10000000000001000");
    auto num5 = num3 + num4;
    assert(num5.to_string() == "20000000000000001");

    lint p1(1);
    lint p2(2);
    lint n1(-1);
    lint n2(-2);
    assert(p1 + p2 == 3);
    assert(p2 - p1 == 1);
    assert(p1 - p2 == -1);
    assert(p1 + n1 == 0);
    assert(p1 + n2 == -1);
    assert(p2 + n1 == 1);
    assert(n1 + n2 == -3);
    assert(n1 - n2 == 1);
    assert(n1 - n1 == 0);
    assert(n2 - n1 == -1);

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

    lint num("-2151319519250942926957424185606849596061442384485818807166972142674771968");
    lint second("-3182150698190905819102845827987336239061910786797723967404482560532676608");
    lint res(num - second);
    assert(res.to_string() == "1030831178939962892145421642380486643000468402311905160237510417857904640");

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
    auto res = num5 * num4;
    assert((num5 * num4).to_string() == "83427032874670095973945907379893169476596773290186076");
    assert(num4 * 1 == num4);
    assert((-1 * num4).to_string() == (-num4).to_string());

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
    auto res3(a / b2);
    assert(res3 == res2);
    assert(res3.is_small());

    lint a1("11620050176394463397996547812951676338039007590238314705568399360");
    auto res4(a1 / 4271);
    assert((a1 / 4271).to_string() == "2720686063309403745726187734242958636862329100968933436096558");

    lint c1("978739441777130566209148083226836080409622025180423218431170079971344384");
    lint c2("-5207251993928654173507308475415265280");
    c1 /= c2;
    assert(c1.to_string() == "-187956995919975159440717122274300878");

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
    lint minimum(-INT32_MAX);
    lint maximum(INT32_MAX);

    assert(minimum.is_small());
    assert(minimum-- == -INT32_MAX);
    assert(!minimum.is_small());

    assert(++minimum == -INT32_MAX);
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
    lint num(324);

    assert(pow(num, 1) == num);
    assert(pow(num, 0) == 1);

    auto result(pow(num, 67));
    assert(result.to_string() == "1608850477873393438550925367579398393660470992312595011124264875206840084023209828465699264821859558494021748709231957337229528619304918410007975008823181918635005313024");
}

void from_string_test()
{
    lint num1("12323434");
    assert(num1.is_small());

    lint num2("123235");
    assert(num2.is_small());

    lint num3("1000000000");
    assert(num3.is_small());

    lint num4("10000000010");
    lint num5("999999999");
    lint num6("-1");
    lint num7("-0000000000000000000000000000000000000000000000000000000000001");
    lint num8("0000000000000000000000000000000000000000000000000000000000001");
    lint num9("+0000000000000000000000000000000000000000000000000000000000001");
    lint num10("-999999999");
//    auto result = num1 + 2 * num2 + 3 * num3 + 4 * num4;
//    assert(lint("6012569909") == result - num5);

    std::cout << "from string tests passed" << std::endl;
}

void my_vector_tests()
{
    using namespace helpers;
    bits vector1(0);
    bits vector2(34);
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
    auto vector5(vector1);
    auto vector6(vector1);
    auto vector7(vector1);
    auto vector8(vector1);
    auto vector9(vector1);

    vector6[0] = 2;
    vector9[vector1.size() - 1] = 5;

    std::cout << "vector_old tests passed" << std::endl;
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

void long_short_div_tests()
{
    
}

void long_long_div_tests()
{
    lint num1("-3337685018533711592795871667265218987553187864987592273118827203149168640");
    lint num2("-337922113784322481219260974202273723021564191665655367473357206667132928");
    assert(-num1 / -num2 == 9);
    auto res = num1 / num2;
    assert(res == 9);
}

void positive_negative_div_tests()
{
    lint num1("-2335710347765676070248101396666744997854320558980944725163584962019983360");
    lint num2("-3033133504283735774253788073215218217783737653671023249380399954094194688");
    assert(-num1 / -num2 == 0);
    auto res = num1 / num2;
    assert(res == 0);

    lint num5("-100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    lint num6("-98000000000000000067031774569072199900349627814759748994040650805381640489125241538626977793");
    assert(num5 / num6 == lint("1"));

    lint num3("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    lint num4("9999999999999999931398190359470212947659194368");
    num3 /= num4;
    assert(num3 == lint("10000000000000000068601809640529787522961634227"));
}

void start_my_tests()
{
    my_vector_tests();

    eq_cmp_tests();

    from_string_test();
    to_string_tests();

    plus_tests();
    minus_tests();
    mul_tests();
    div_tests();
    long_short_div_tests();
    long_long_div_tests();
    positive_negative_div_tests();
    cmp_tests();
    
    increment_tests();
    decrement_tests(); 
    abs_tests();
    pow_tests();
    casts_tests();
    great_test();
}
