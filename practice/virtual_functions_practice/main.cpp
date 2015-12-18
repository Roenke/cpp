
#include "my_ostream_con.h"
#include "my_ostream_file.h"
#include <vector>
my_ostream_con cout;
my_ostream_file cerr("error.txt");

void streams_tests()
{
    std::vector<my_ostream*> stream_ptrs = { &cout, &cerr };
    *stream_ptrs[0] << "Hello world\n" << "int test: " << 10 << "\ndouble test: " << 10.0 << "\nComplete.\n";
    *stream_ptrs[1] << "Hello world\n" << "int test: " << 10 << "\ndouble test: " << 10.0 << "\nComplete.\n";
}

int main()
{
    streams_tests();
}
