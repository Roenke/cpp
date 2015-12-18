#include "shared_buffer.h"
#include <cassert>
#include "vector.h"
#include <vector>

void vector_tests()
{
    vector<int> vect1(10);
    std::vector<int> vect4(10);
    vect4.assign(10, 2);
    
    vector<double> vect2(100);
    assert(vect1.size() == 10);
    assert(vect2.size() == 100);

    vect1[0] = 0;
    auto vect3(vect1);
    assert(vect3[0] == 0);
    vect3[0] = 1;
    assert(vect1[0] == vect1[0]);
    assert(vect1[0] != vect3[0]);
    vector<int> vect6(1);
    for (int i = 0; i < 1000; ++i)
    {
        vect6.push_back(i);
    }

    assert(vect6.size() == 1001);
    assert(vect6[1000] == 999);
    auto vect7(vect6);
    for (int i = 0; i < 1000; ++i)
    {
        (void)vect6.pop_back();
    }
    assert(vect6.size() == 1);
    assert(vect7.size() == 1001);

    auto vect8(vect7);
    vect8[0] = 1000;
}

int main()
{
    vector_tests();
}
