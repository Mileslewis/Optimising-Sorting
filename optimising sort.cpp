// optimising sort.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <tuple>
#include <iostream>
#include <array>
#include <chrono>

const int g_Elem = 10; //number of array elements
void printArray(std::array<int, g_Elem> &array)      //prints the array
{
	std::cout << "( "<<array[0];
	for (int index = 1; index < g_Elem; ++index)
	{
		std::cout << ", " << array[index] ;
	}
	std::cout << ")\n";
}

void sortArray(std::array<int, g_Elem> &array)   //asscending sort by placing smallest in first element then next smallest in second element etc.
{

	for (int startIndex = 0; startIndex < g_Elem - 1; ++startIndex)
	{
		//smallestIndex is the index of the smallest element we’ve encountered this iteration
		//Start by assuming the smallest element is the first element of this iteration
		int smallestIndex = startIndex;

		//then look for a smaller element in the rest of the array
		for (int currentIndex = startIndex + 1; currentIndex < g_Elem; ++currentIndex)
		{
			//If we've found an element that is smaller than our previously found smallest
			if (array[currentIndex] < array[smallestIndex])
				//then keep track of it
			{
				smallestIndex = currentIndex;
			}
		}

		// smallestIndex is now the smallest element in the remaining array
		// swap our start element with our smallest element (this sorts it into the correct place)
		{
			std::swap(array[startIndex], array[smallestIndex]);
	
			printArray(array); //used for debugging
		}
	}
}
void swapSortArray(std::array<int, g_Elem> &array) //ascending sort by going through array and swapping any two adjecent elements which are descending until no more swaps can be done
{
	bool b = false; //used to see if we have swapped so we know when to stop
	do
	{
		bool b = false; //reset to false each time we go through array
		for (int index = 0; index < g_Elem-1; ++index) //go through array swapping any elements to put smaller one first.
		{
			if (array[index] > array[index + 1])
			{
				std::swap(array[index], array[index + 1]);
				printArray(array); //debugging
				b = true; //if we have done a swap we should check the array again
			}
		}
	}
	while (b = true); //repeat if swap was done
}

int main()
{
     //create an array to test and print it
	std::array<int, g_Elem> array;
	for (int i = 0; i < g_Elem; ++i)
		array[i] = g_Elem- i;
    printArray(array); // debugging



	swapSortArray(array);


	printArray; //debugging

	return 0;
}


