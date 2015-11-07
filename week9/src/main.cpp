#include <iostream>
#include "my_stream_con.h"
#include "my_stream_file.h"
my_stream_con cout;
//my_stream_file cerr("error.txt");

int main()
{
    cout << "Hello polymorphic world";
    // cerr << "Error happened. What = undefined";
}