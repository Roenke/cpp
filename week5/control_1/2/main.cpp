#include <iostream>
#include <fstream>

void append(int**arr, int addedElem, int& count, int& size)
{
	
	if (count == size)
	{
		int* newArray = new int[size * 2];
		for (int i = 0; i < count; ++i)
		{
			newArray[i] = (*arr)[i];
		}
		size *= 2;
		*arr = newArray;
	}
	(*arr)[count] = addedElem;
	count++;
}


int main()
{
	using namespace std;
	int n;
	fstream inFile;
	inFile.open("input.txt", ios::in);
	int number;
	int count = 0;
	int size = default_array_size;
	int* array = new int[size];
	while(inFile >> number)
	{
		append(&array, number, count, size);
	}

	merge_sort(array, count);

	fstream outFile;
	outFile.open("output.txt", ios::out);
	for (int i = 0; i < count; ++i)
	{
		outFile << array[i] << " ";
	}

	delete[] array;
}