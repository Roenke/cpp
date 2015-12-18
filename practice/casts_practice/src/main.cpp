#include <iostream>
#include "command.h"
const int buffer_size = 1000;

enum command {
	add,
	float_sum,
	google_search,
	palindrome,
	quit,
	show,
	show_memory,
	sub,
	unknown
};

enum error
{
	wrong_int,
	wrong_double,
	wrong_hex_int
};

command read_next_command() {
	char command;
	std::cin >> command;
	switch (command) {
	case 'a': return add;
	case 'f': return float_sum;
	case 'm': return show_memory;
	case 'p': return palindrome;
	case 'q': return quit;
	case 'r': return show;
	case 's': return sub;
	default: return unknown;
	}
}

int main() {
	int result = 0;
	char buffer[buffer_size];
	int intArg;
	double doubleArg;
	bool isContinue = true;
	using namespace std;
	while (isContinue) {
		command com = read_next_command();
		try
		{
			switch (com) {
			case add:
				cin >> intArg;
				cin.fail() ? throw wrong_int : add_command(result, intArg);
				break;
			case sub:
				cin >> intArg;
				cin.fail() ? throw wrong_int : sub_command(result, intArg);
				break;
			case show:
				print_command(result);
				break;
			case float_sum:
				cin >> doubleArg;
				cin.fail() ? throw wrong_double : float_sum_command(result, doubleArg);
				break;
			case palindrome:
				cin.getline(buffer, buffer_size);
				palindrome_command(buffer);
				break;
			case quit:
				isContinue = false;
				break;
			case google_search:
				cin.getline(buffer, buffer_size);
				google_search_command(buffer);
				break;
			case show_memory:
				uintptr_t address;
				int count;
				cin >> hex >> address;
				if (cin.fail())
					throw wrong_hex_int;
				cin >> count;
				cin.fail() ?  throw wrong_int : show_memory_command(address, count);
				break;
			case unknown:
				on_unknown_command();
				break;
			default:
				break;
			}
		}
		catch(error error_code)
		{
			switch (error_code)
			{
			case wrong_int:
				cout << "Need valid decimal integer value" << endl;
				break;
			case wrong_double:
				cout << "Need valid decimal float value" << endl;
				break;
			case wrong_hex_int:
				cout << "Need valid hex integer value" << endl;
			}
			cin.clear();
		}
	}
}
