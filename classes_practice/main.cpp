#include "shared_buffer.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include "lazy_string.h"

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

void main()
{
    shared_buffer_tests();

    lazy_string_tests();
}
