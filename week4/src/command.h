#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string.h>

void add_command(int& result, int arg);

void sub_command(int& result, int arg);

void float_sum_command(int& result, double arg);

void google_search_command(char* query);

void check_for_palindrome(char* str, int& down, int& upper, int length);

void palindrome_command(char* str);

void show_memory_command(int address, int count);

void print_command(int result);

void on_unknown_command();

#endif