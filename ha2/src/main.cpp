#include "lint.h"
#include "mytests.h"
#include "tests.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main()
{
    //start_all();
    double d = 123.5456e+234;
    auto str_d = std::to_string(d);
    auto point_index = str_d.find('.');
    auto a = apa::lint(str_d.substr(0, point_index));
    std::cout << std::to_string(d).find('.');
    start_my_tests();
    return 0;
}
