#include <cassert>
#include <string>

#include <iostream>
#include "any.h"

namespace utils{
    class any;
}

using utils::any;
using utils::any_cast;
using utils::bad_any_cast;

using std::string;
using std::cout;
using std::cerr;
using std::endl;

void contruct_test()
{
    any def;
    any copy_on_type(42);

    def = 3.14;
    def = string("2.71");
    any def_copy(def);
    def = copy_on_type;
    any e;
    assert(e.empty());
}

template<class T>

void check_cast(any& a, bool should_throw)
{
    bool thrown = false;
    try
    {
        double res = any_cast<T>(a);
        std::cout << res;
    }

    catch (bad_any_cast const& err)
    {
        thrown = true;
        std::cerr << err.what() << std::endl;
    }

    assert(should_throw == thrown);

}

void retrieve_value_test()
{
    any ia(42);
    auto res = any_cast<double*>(&ia);
    assert(res == nullptr);
    check_cast<double>(ia, true);
    check_cast<int> (ia, false);
}

void swap_test(any& a, any& b)
{
    swap(a, b);
}

void my_tests()
{
    any a1(10);
    auto a2(a1);
    auto a3 = a2;

    any a4{};
    assert(a4.empty());
    a4 = 5;
    assert(a4.type() == a1.type());

    a1 = 'c';
    assert(a1.type() != a2.type());

    bool throwed = false;
    try
    {
        auto a = any_cast<std::exception>(a1);
    }
    catch(bad_any_cast const& e)
    {
        cout << e.what() << endl;
        throwed = true;
    }

    assert(throwed);
}

int main()
{
    contruct_test();
    retrieve_value_test();

    any a(5), b(string("6"));
    swap_test(a, b);

    my_tests();

    return 0;
}
