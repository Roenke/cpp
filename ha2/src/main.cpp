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
    std::ostringstream ost;
    ost << d;
    std::cout << std::fixed << d << std::endl;
    start_my_tests();
    return 0;
}
