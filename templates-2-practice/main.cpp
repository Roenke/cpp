#include <iostream>
#include "scoped_ptr.h"
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
    }

    std::cout << "foo_ptr must be deleted" << std::endl;
#ifdef COMPILE_MUST_FAILED
    foo_ptr = std::move(foo_ptr);
    auto foo_ptr2(foo_ptr);
    foo_ptr = foo_ptr;
    bool_1st_arg_func(foo_ptr);
#endif
}

void test_shared()
{
    
}

void test_unique()
{
    
}

void main() 
{
    test_scoped();

    test_shared();

    test_unique();
}
