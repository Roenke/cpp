#!/usr/bin/env python3

import random

test_count = 100000
max_value = 3000000000


def generate_mul():
    with open('mul.test', 'w') as file:
        file.write('%d\n' % test_count)
        for i in range(test_count):
            l = int(random.uniform(-max_value, max_value))
            r = int(random.uniform(-max_value, max_value))
            file.write("%d %d %d\n" % (l, r, l * r))


def generate_div():
    with open('div.test', 'w') as file:
        file.write('%d\n' % (12 * test_count))
        for i in range(test_count):
            l = int(random.uniform(0, max_value))
            r = int(random.uniform(100000, max_value))
            addition = 0 if l % r == 0 else 1
            file.write("%d %d %d\n" % (l, r, l // r))
            file.write("%d %d %d\n" % (-l, r, -l // r + addition))
            file.write("%d %d %d\n" % (l, -r, l // -r + addition))
            file.write("%d %d %d\n" % (-l, -r, -l // -r))
        for i in range(test_count):
            l = int(random.uniform(0, max_value))
            r = int(random.uniform(1, 10000))
            addition = 0 if l % r == 0 else 1
            file.write("%d %d %d\n" % (l, r, l // r))
            file.write("%d %d %d\n" % (-l, r, -l // r + addition))
            file.write("%d %d %d\n" % (l, -r, l // -r + addition))
            file.write("%d %d %d\n" % (-l, -r, -l // -r))

        for i in range(test_count):
            l = int(random.uniform(0, max_value))
            r = int(random.uniform(1, 10000000000000000000000000000000000000))
            addition = 0 if l % r == 0 else 1
            file.write("%d %d %d\n" % (l, r, l // r))
            file.write("%d %d %d\n" % (-l, r, -l // r + addition))
            file.write("%d %d %d\n" % (l, -r, l // -r + addition))
            file.write("%d %d %d\n" % (-l, -r, -l // -r))


def generate_sum():
    with open('sum.test', 'w') as file:
        file.write('%d\n' % test_count)
        for i in range(test_count):
            l = int(random.uniform(0, max_value))
            r = int(random.uniform(-max_value, max_value))
            file.write("%d %d %d\n" % (l, r, l + r))


def generate_sub():
    with open('sub.test', 'w') as file:
        file.write('%d\n' % test_count)
        for i in range(test_count):
            l = int(random.uniform(-max_value, max_value))
            r = int(random.uniform(-max_value, max_value))
            file.write("%d %d %d\n" % (l, r, l - r))
            file.write("%d %d %d\n" % (r, l, r - l))


def main():
    generate_mul()
    generate_div()
    generate_sum()
    generate_sub()

if __name__ == '__main__':
    main()
