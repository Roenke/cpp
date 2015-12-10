#!/usr/bin/env python3

import random

test_count = 10000
max_value = 3845734875678342583745982347582945732849573248957329857348956378246873465


def generate_mul():
    with open('mul.txt', 'w') as file:
        file.write('%d\n' % test_count)
        for i in range(test_count):
            l = int(random.uniform(-max_value, max_value))
            r = int(random.uniform(-max_value, max_value))
            file.write("%d %d %d\n" % (l, r, l * r))


def generate_div():
    with open('div.txt', 'w') as file:
        file.write('%d\n' % (8 * test_count))
        for i in range(test_count):
            l = int(random.uniform(0, max_value))
            r = int(random.uniform(100000, max_value))
            file.write("%d %d %d\n" % (l, r, l // r))
            file.write("%d %d %d\n" % (-l, r, -l // r))
            file.write("%d %d %d\n" % (l, -r, l // r))
            file.write("%d %d %d\n" % (-l, -r, l // r))
        for i in range(test_count):
            l = int(random.uniform(0, max_value))
            r = int(random.uniform(1, 10000))
            file.write("%d %d %d\n" % (l, r, l // r))
            file.write("%d %d %d\n" % (l, -r, -l // r))
            file.write("%d %d %d\n" % (-l, r, -l // r))
            file.write("%d %d %d\n" % (-l, -r, l // r))


def generate_sum():
    with open('sum.txt', 'w') as file:
        file.write('%d\n' % test_count)
        for i in range(test_count):
            l = int(random.uniform(0, max_value))
            r = int(random.uniform(-max_value, max_value))
            file.write("%d %d %d\n" % (l, r, l + r))


def generate_sub():
    with open('sub.txt', 'w') as file:
        file.write('%d\n' % test_count)
        for i in range(test_count):
            l = int(random.uniform(-max_value, max_value))
            r = int(random.uniform(-max_value, max_value))
            file.write("%d %d %d\n" % (l, r, l - r))
            file.write("%d %d %d\n" % (r, l, r - l))


def get_n_fib(n):
    prev = 1
    prevprev = 1
    for i in range(n - 2):
        prevprev,prev = prev, prevprev + prev
    return prev


def generate_fib_seq():
    with open('fib.test', 'w') as file:
        for i in range(test_count):
            n = int(random.uniform(3, 1500))
            file.write('%d %d\n' % (n, get_n_fib(n)))


def gen_n_fact(n):
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result


def generate_fact_seq():
    with open('fact.test', 'w') as file:
        for i in range(test_count):
            n = int(random.uniform(3, 200))
            file.write('%d %d\n' % (n, gen_n_fact(n)))


def main():
    generate_mul()
    generate_div()
    generate_sum()
    generate_sub()
    generate_fib_seq()
    generate_fact_seq()

if __name__ == '__main__':
    main()