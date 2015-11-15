#include <iostream>
#include <fstream>
#include "mergesort.h"
int main()
{
	using namespace std;
	int number;
	int count = 0;
	int arraySize = 10000;
	int i = 0;
	int* array = new int[arraySize];
	while(cin >> number)
	{
		array[i] = number;
	}
	int size = i;
	merge_sort(array, size);

	for (int i = 0; i < count; ++i)
	{
		cout << array[i] << " ";
	}

	delete[] array;
}