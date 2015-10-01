#include "mergesort.h"

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