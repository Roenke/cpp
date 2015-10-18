#include <iostream>
#include <fstream>

const size_t aplhabet_count = 256;

size_t frequencies[aplhabet_count];
int main(int argc, char* argv[])
{
	using namespace std;
	if (argc != 2)
	{
		cout << "Wrong number of arguments";
		return 1;
	}

	// for (size_t i = 0; i < aplhabet_count; ++i)
	// {
	// 	frequencies[aplhabet_count] = 0;
	// }

	char* filename = argv[1];

	ifstream file;
	file.open(filename, ifstream::binary);

	file.seekg(0, file.end);
	cout << "Total in file: " << file.tellg();
	file.seekg(0, file.beg);
	size_t index;
	char ch;
	size_t counter = 0;
	while (file.read(&ch, 1))
	{
		index = (uint8_t)ch;
		frequencies[index]++;
		counter++;
	}
	cout << "Total readed: " << counter << endl;

	for (size_t i = 0; i < aplhabet_count; ++i)
	{
		cout << (int)i << " : " << frequencies[i] << endl;
	}

	return 0;
}