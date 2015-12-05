#include <iostream>
#include "scoped_ptr.h"
#include <cassert>
#include "unique_ptr.h"

// #define COMPILE_MUST_FAILED
struct foo
{
    foo(int a, int b){
        field1 = a;
        field2 = b;
    }

    int field1;
    int field2;

    ~foo()
    {
        std::cout << "delete foo (" << field1 << ", " << field2 << ") " << std::endl;
    }
};


void test_scoped()
{
    {
        my_ptrs::scoped_ptr<foo> foo_ptr(new foo(3, 4));
        std::cout << (*foo_ptr).field1 << foo_ptr->field1 << foo_ptr.get() << std::endl;

        if (foo_ptr) {
            foo_ptr->field1 += 1;
        }

        assert(foo_ptr.get()->field1 == 4);
        assert(foo_ptr.get()->field2 == 4);

        foo_ptr.reset();
        assert(!foo_ptr);

        foo_ptr.reset(new foo(2, 5));
        assert(foo_ptr);
        assert(foo_ptr.get()->field1 == 2);

        foo_ptr.reset();
        bool throwed = false;
        try
        {
            foo_ptr->field1 = 4;
        }
        catch(my_ptrs::npe_exception const& ex)
        {
            throwed = true;
            std::cerr << ex.what() << std::endl;
        }

        assert(throwed == true);
    }

    std::cout << "foo_ptr must be deleted" << std::endl;

    std::cout << "Scoped ptr passed tests." << std::endl;
#ifdef COMPILE_MUST_FAILED
    foo_ptr = std::move(foo_ptr);
    auto foo_ptr2(foo_ptr);
    foo_ptr = foo_ptr;
    bool_1st_arg_func(foo_ptr);
#endif
}

my_ptrs::unique_ptr<foo> create_foo()
{
    auto result(new foo(666, 777));
    return result;
}

int get_field1(my_ptrs::unique_ptr<foo> foo)
{
    return foo->field1;
}

void test_unique()
{
    using namespace my_ptrs;
    my_ptrs::unique_ptr<foo> foo_ptr(new foo(666, 777));
    auto foo_ptr_shared = std::move(foo_ptr);
    
    assert((*foo_ptr_shared).field1 == 666);

    auto foo_ptr_shared_again = std::move(foo_ptr_shared);

    assert(foo_ptr_shared_again.get()->field2 == 777);

    assert(foo_ptr_shared_again);

    auto throwed = false;

    try
    {
        std::cerr << foo_ptr->field1 << std::endl;
    }
    catch(npe_exception const& ex)
    {
        throwed = true;
        std::cerr << ex.what() << std::endl;
    }

    assert(throwed == true);
#ifdef COMPILE_MUST_FAILED
    auto foo_ptrs_fails(foo_ptr_shared_again);
#endif

    auto func_ptr = create_foo();

    assert(func_ptr->field2 == 777);

    assert(get_field1(create_foo()) == 666);
    std::cout << "Unique ptr passed tests." << std::endl;
}

void test_shared()
{

}

void main() 
{
    test_scoped();

    test_unique();

    test_shared();
}
