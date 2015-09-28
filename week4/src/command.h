#ifndef COMMAND_H
#define COMMAND_H
#include <stdint.h>
void add_command(int& result, int arg);

void sub_command(int& result, int arg);

void float_sum_command(int& result, double arg);

void google_search_command(const char* query);

void palindrome_command(const char* str);

void show_memory_command(uintptr_t address, int count);

void print_command(int result);

void on_unknown_command();

#endif