#include <cstdint>
#include <iostream>
#include <cassert>

// practice 3. fall 2015 spbau

void address_order()
{
    char stack_mem1[2];
    char stack_mem2[2];
    auto heap_mem1 = new char[2];
    auto heap_mem2 = new char[2];
    auto first_stack_addr = reinterpret_cast<int>(stack_mem1);
    auto second_stack_addr = reinterpret_cast<int>(stack_mem2);

    auto first_heap_addr = reinterpret_cast<int>(heap_mem1);
    auto second_heap_addr = reinterpret_cast<int>(heap_mem2);

    auto delta_stack = second_stack_addr - first_stack_addr;
    auto delta_heap = second_heap_addr - first_heap_addr;

    assert(delta_stack < 0);

    std::cout << "delta stack = " << delta_stack << std::endl;
}


int step_count(int n)
{
    uint32_t steps[21];
    steps[0] = 1;
    steps[1] = 2;
    for (int i = 2; i < 21; ++i)
    {
        steps[i] = steps[i - 1] + steps[i - 2];
    }

    if(n > 21 || n < 1)
    {
        throw std::exception("wrong stairs size");
    }

    return steps[n - 1];
}

void step_count_tests()
{
    assert(step_count(1) == 1);
    assert(step_count(2) == 2);
    assert(step_count(3) == 3);
}

const char* concat(const char a[], const size_t a_size, const char b[], const size_t b_size, size_t &concat_size)
{
    concat_size = a_size + b_size;
    auto result = new char[concat_size];
    
    memcpy(result, a, a_size);
    memcpy(result + a_size, b, b_size);
    
    return result;
}

void concat_tests()
{
    char a[10] = { 0,1,3,4,5 };
    char b[3] = { 1,1,1 };
    size_t concat_size;
    auto res1 = concat(a, 10, b, 3, concat_size);
    assert(concat_size == 13);
    assert(res1[0] == 0);
    assert(res1[2] == 3);
    assert(res1[10] == 1);
    assert(res1[9] == 0);
    assert(res1[12] == 1);

    auto res2 = concat(b, 3, a, 10, concat_size);
    assert(concat_size == 13);
    assert(res2[0] == 1);
    assert(res2[1] == 1);
    assert(res2[3] == 0);
    assert(res2[12] == 0);

    delete[] res1;
    delete[] res2;

    std::cout << "Concat tests passed" << std::endl;
}

int** create_matrix(int n, int m)
{
    auto result = new int[m * n];
    auto matrix = new int*[n];
    matrix[0] = result;
    for (int i = 1; i < n; ++i)
    {
        matrix[i] = matrix[i - 1] + m;
    }

    return matrix;
}

void fill_matrix(int** matrix, int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            matrix[i][j] = 2 * i + j;
        }
    }
}

void pretty_indexation_tests()
{
    auto matrix = create_matrix(3, 5);
    fill_matrix(matrix, 3, 5);
    assert(matrix[2][1] == 5);
    assert(matrix[1][2] == 4);
    assert(matrix[0][0] == 0);
    assert(matrix[1][0] == 2);
    assert(matrix[0][1] == 1);

    delete[] matrix[0];
    delete[] matrix;

    std::cout << "matrix tests passed" << std::endl;
}

void main()
{
    address_order();
    step_count_tests();
    concat_tests();

    pretty_indexation_tests();
}
