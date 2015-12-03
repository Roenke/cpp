#include "shared_buffer.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include "lazy_string.h"

using namespace lazy;

void shared_buffer_tests()
{
    shared_buffer buf(100);
    auto data = buf.get_data();
    data[0] = 'a';
    data[1] = 'b';
    data[2] = '\0';
    const char* const_data = buf.get_data();
    assert(const_data[0] == data[0]);
    assert(const_data[2] == data[2]);
    assert(const_data == data);

    auto buf_copy(buf);
    assert(buf_copy.get_data()[0] == buf.get_data()[0]);
    assert(buf.get_size() == buf_copy.get_size());
    assert(buf_copy.get_data() == buf_copy.get_data());
    assert(strcmp(buf_copy.get_data(), buf.get_data()) == 0);

    std::cout << "Shared buffer passed tests" << std::endl;
}

void lazy_string_tests()
{
    lazy_string ls("hello");
    auto ls2(ls);
    auto ls3(ls2);

    assert(ls2.empty() == false);
    assert(ls2.get_at(2) == 'l');
    assert(ls3.empty() == false);

    lazy_string begin("Lazy string ");
    lazy_string end("passed tests.");

    print(std::cout, concat(begin, end));
}


void lazy_copy_on_write_tests()
{
    lazy_string ls1("my string");

    auto ls2 = ls1;
    auto ls3(ls2);

    ls1.set_at(1, 'o');
    ls2.set_at(1, 'p');
    assert(ls3.get_at(1) == 'y');
    assert(ls1.get_at(1) == 'o');
    assert(ls2.get_at(1) == 'p');

    lazy_string begin("Lazy copy on write string ");
    lazy_string end("passed tests.");

    print(std::cout, concat(begin, end));
}

void lazy_find_tests()
{
    lazy_string ls("Hello world");

    size_t result = 0;
    assert(find(ls, "hello", result) == false);
    assert(result == 0);

    assert(find(ls, "Hello", result) == true);
    assert(result == 0);

    assert(find(ls, "Hello", result, 1));
    assert(result == 0);

    assert(find(ls, "world", result, 2) == true);
    assert(result == 6);

    std::cout << "Find in lazy strings passed tests" << std::endl;
}

void lazy_operators_tests()
{
    lazy_string ls("My test text");
    std::cout << ls;

    lazy_string lsa("Hello ");
    lazy_string lsb("world");
    lsa += lsb;
    
    lsa += lsb + lsa;

    assert(!lsa.empty());
    assert(lsa.get_at(0) == 'H');
    
    lsa[3] = 'y';
    assert(lsa[1] == 'e');
    assert(lsa[3] != 'l');

    assert(lazy_string("a") < lazy_string("bbb"));
    assert(lazy_string("abba") < lazy_string("abbb"));
    assert(!(lazy_string("qwertyy") < lazy_string("qwerty")));

    std::cout << lsa;
}

void main()
{
    shared_buffer_tests();

    lazy_string_tests();

    lazy_copy_on_write_tests();

    lazy_find_tests();

    lazy_operators_tests();
}
