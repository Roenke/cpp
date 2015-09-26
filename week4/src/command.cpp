#include "command.h"

const char* google_search_prefix = "https://www.google.ru/search?q=";

void add_command(int& result, int arg) {
	result += arg;
}

void sub_command(int& result, int arg) {
	add_command(result, -arg);
}

void float_sum_command(int& result, double arg)
{
	result += static_cast<int>(arg);;
}

void google_search_command(char* query)
{
	int length = strlen(query);
	std::cout << google_search_prefix;
	for (int i = 0; i < length; i++)
	{
		if (query[i] == ' ')
			std::cout << "%20";
		else
		{
			std::cout << query[i];
		}
	}
	std::cout << std::endl;
}

void check_for_palindrome(char* str, int& down, int& upper, int length)
{
	while (down >= 0 && upper < length && str[down] == str[upper])
	{
		down--;
		upper++;
	}
	upper--;
	down++;
}

void palindrome_command(char* str)
{
	int length = strlen(str);
	int max_length = 1;
	int max_upper = 0;
	int max_down = 0;
	int upper, down;
	for (int i = 1; i < length - 1; i++)
	{
		upper = i + 1;
		down = i - 1;
		check_for_palindrome(str, down, upper, length);
		if (upper - down + 1 >= max_length)
		{
			max_down = down;
			max_upper = upper;
			max_length = upper - down + 1;
		}
		upper = i;
		down = i - 1;
		check_for_palindrome(str, down, upper, length);
		if (upper - down + 1 >= max_length)
		{
			max_down = down;
			max_upper = upper;
			max_length = upper - down + 1;
		}
	}

	for (int i = max_down; i <= max_upper; i++)
		std::cout << str[i];
	std::cout << std::endl;
}

void show_memory_command(int address, int count)
{
	char* addr = reinterpret_cast<char*>(address);
	for (int i = 0; i < count; i++)
	{
		std::cout << addr[i];
	}
	std::cout << std::endl;
}

void print_command(int result)
{
	std::cout << ">>>" << result << std::endl;
}

void on_unknown_command()
{
	std::cout << "Wrong command" << std::endl;
}