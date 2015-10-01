#include <iostream>
#include <fstream>
#include "mergesort.h"
const int default_array_size = 10;

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

void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void merge_sort(int* array, size_t size)
{
	if(size == 1)
	{
		return;
	}

	if(size == 2)
	{
		if(array[0] < array[1])
		{
			swap(array[0], array[1]);
		}
		return;
	}

	

	size_t middle = size / 2;
	
	int* left = new int[middle];
	for (int i = 0; i < middle; ++i)
	{
		left[i] = array[i];
	}
	int* right = new int[size - middle];
	for (int i = middle; i < size; ++i)
	{
		right[i - middle] = array[i];
	}
	merge_sort(left, middle);
	merge_sort(right, size - middle);
	
	int leftPtr = 0;
	int rightPtr = 0;
	
	for (int i = 0; i < size; ++i)
	{
		if(leftPtr >= middle)
		{
			array[i] = right[rightPtr];
			rightPtr++;
		}
		else if(rightPtr >= size - middle)
		{
			array[i] = left[leftPtr];
			leftPtr++;
		}
		else if(left[leftPtr] > right[rightPtr])
		{
			array[i] = left[leftPtr];
			leftPtr++;
		}
		else
		{
			array[i] = right[rightPtr];
			rightPtr++;
		}
	}
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