#include "shared_buffer.h"
#include <cassert>
#include <cstring>
#include <iostream>

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

void main()
{
    shared_buffer_tests();
}
