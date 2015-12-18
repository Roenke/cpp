#include <iostream>
#include "operators.h"
#include <cassert>
#include "queue.h"
#include "priority_queue.h"

int generator()
{
    static auto i = 10;
    return i++;
}

double double_generator()
{
    static auto i = 1.;
    return i++;
}

double fib_generator()
{
    static double prev = 1;
    static double prev_prev = 0;

    auto old_val = prev_prev;
    prev_prev = prev;
    prev = old_val + prev;
    
    return prev;
}

double sqr_functor(double arg)
{
    return arg * arg;
}

double sum_double_acc(double a, double b)
{
    return a + b;
}

void fill_tests()
{
    auto int_array = new int[10];
    fill(&int_array[0], &int_array[5], 0);
    fill(&int_array[5], &int_array[10], 5);
    assert(int_array[0] == 0);
    assert(int_array[4] == 0);
    assert(int_array[5] == 5);
    assert(int_array[9] == 5);

    std::cout << "fill tests passed" << std::endl;
}


void print_tests()
{
    auto int_array = new int[10];
    fill(&int_array[0], &int_array[5], 0);
    fill(&int_array[5], &int_array[10], 5);

    print(int_array, 10);

    std::cout << "print tests passed" << std::endl;
}

void copy_tests()
{
    auto int_array_new = new int[10];
    fill(&int_array_new[0], &int_array_new[5], 0);
    fill(&int_array_new[5], &int_array_new[10], 5);
    auto int_array = new int[10];
    copy(&int_array_new[0], &int_array_new[10], int_array);

    assert(int_array[0] == 0);
    assert(int_array[4] == 0);
    assert(int_array[5] == 5);
    assert(int_array[9] == 5);

    std::cout << "copy tests passed" << std::endl;
}

void generate_tests()
{
    auto double_arr = new double[10];
    fill(&double_arr[0], &double_arr[10], 0.);
    generate(&double_arr[0], &double_arr[10], double_generator);

    assert(double_arr[0] == 1.);
    assert(double_arr[2] == 3.);
    assert(double_arr[9] == 10.);

    std::cout << "generate tests passed" << std::endl;
}

void for_each_tests()
{
    auto double_arr = new double[10];
    fill(&double_arr[0], &double_arr[10], 0.);
    generate(&double_arr[0], &double_arr[10], double_generator);
    for_each(&double_arr[0], &double_arr[10], sqr_functor);

    assert(double_arr[0] == 121.);
    assert(double_arr[2] == 169.);

    std::cout << "for_each tests passed" << std::endl;
}

void accumulate_tests()
{
    auto double_arr = new double[10];
    generate(&double_arr[0], &double_arr[10], fib_generator);

    assert(double_arr[8] == 55);
    assert(accumulate(&double_arr[0], &double_arr[10], sum_double_acc) == 231);

    std::cout << "accumulate tests passed" << std::endl;
}

void queue_tests()
{
    data_structures::queue<double> double_queue;
    data_structures::queue<int> int_queue;

    double_queue.push(10.);
    double_queue.push(234.);

    assert(double_queue.size() == 2);
    assert(double_queue.pop() == 10.);
    assert(double_queue.size() == 1);
    assert(double_queue.front() == 234.);
    assert(double_queue.pop() == 234.);
    assert(double_queue.size() == 0);

    auto throwed = false;

    try
    {
        (void)double_queue.pop();
    }
    catch (std::exception const&)
    {
        throwed = true;
    }

    assert(throwed);

    int_queue.push(1);
    int_queue.push(2);
    int_queue.push(3);
    int_queue.push(4);

    auto new_int_queue(int_queue);

    assert(new_int_queue.size() == int_queue.size());
    assert(new_int_queue.front() == 1.);

    std::cout << "templated queue tests passed" << std::endl;
}

void priority_queue_tests()
{
    priority_queue<double> double_queue;
    priority_queue<int> int_queue;

    assert(double_queue.size() == 0);
    assert(int_queue.size() == 0);

    double_queue.push(5., 1);
    double_queue.push(10., 2);
    double_queue.push(20.0, 3);

    assert(double_queue.front() == 20.0);
    assert(double_queue.size() == 3);
    double_queue.push(15.0, 2);
    assert(double_queue.size() == 4);
    assert(double_queue.front() == 20.);
    double_queue.pop();
    assert(double_queue.size() == 3);
    assert(double_queue.front() == 15. || double_queue.front() == 10.);
   
    auto copy_double = double_queue;

    assert(copy_double.size() == double_queue.size());
    copy_double.pop();
    assert(copy_double.size() != double_queue.size());
    assert(double_queue.front() == 15. || double_queue.front() == 10.);

    auto copy_copy_double(copy_double);
    assert(copy_copy_double.size() == copy_double.size());
    copy_copy_double.pop();
    assert(copy_copy_double.front() == 5.);
    assert(copy_copy_double.size() != copy_double.size());

    std::cout << "templated priority queue tests passed" << std::endl;
}

void main()
{
    fill_tests();
    print_tests();
    copy_tests();
    generate_tests();
    for_each_tests();
    accumulate_tests();

    queue_tests();

    priority_queue_tests();
}
