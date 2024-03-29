// optimising sort.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <tuple>
#include <iostream>
#include <array>
#include <chrono>
#include <ctime>

const int g_Elem = 10000; //number of array elements
const int g_min = 1;
const int g_max = 10000;

class Timer
{
private:
	//Type aliases to make accessing easier
	using clock_t = std::chrono::high_resolution_clock; //access current time through clock_t::now()
	using second_t = std::chrono::duration<double, std::ratio<1> >; //data type for number of seconds in double format

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now()) //set m_beg to now
	{
	}

	void reset()
	{
		m_beg = clock_t::now(); //reset m_beg to now
	}

	double elapsed() const //time elapsed between when m_beg was set and now
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

void printArray(std::array<int, g_Elem> &array)      //prints the array
{
	std::cout << "( "<<array[0];
	for (int index = 1; index < g_Elem; ++index)
	{
		std::cout << ", " << array[index] ;
	}
	std::cout << ")\n";
}

void sort(std::array<int, g_Elem> &array)   //asscending sort by placing smallest in first element then next smallest in second element etc.
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
	
			//printArray(array); //used for debugging
		}
	}
}
void swapSort(std::array<int, g_Elem> &array) //ascending sort by going through array and swapping any two adjecent elements which are descending until no more swaps can be done
{
	//int checks = 0; //created to see how many times swapSortArray() checked if one element is bigger than another.
	//int swaps = 0; //created to see how many times swapSortArray() swapped two elements
		for (int i = 1; i < g_Elem; ++i) //go through array until you find two ellements which should be swapped
		{
			//++checks; 
			if (array[i] < array[i - 1]) 
			{
				int index = i;
			   // std::cout<<index<<"\n"; //debugging
				do
				{
					//++checks;
					std::swap(array[index], array[index - 1]); //swap it
					//++swaps;
					if (index > 1)
					{
						index--;
						//std::cout << index<<"\n"; //debugging
					}
				  //printArray(array); //debugging
				} 
				while ((array[index] < array[index - 1]));  //then swap it as far down the array as it can go
			}
		}
		//std::cout << checks << " checks\n"; //print how many checks were done
		//std::cout << swaps << " swaps\n"; //print how many swaps were done.
	
}

void preSort(std::array<int,g_Elem> &array)
{
	for (int i = 0; i < g_Elem; i++) //go through each element one by one
	{
		int j= ((array[i] - g_min)*(g_Elem)) / (1+g_max - g_min) ;  //figure out where element i should be based on
		//std::cout << j<<"\n";
		std::swap(array[j], array[i]);
      // printArray(array);
	}
}

int main()
{
     //create an array to test here
	/*
	std::array<int, g_Elem> array;         //this creates a desending array to sort for testing
	for (int i = 0; i < g_Elem; ++i)
		array[i] = g_Elem- i;
		*/
	unsigned int seed = static_cast<unsigned int>(std::time(nullptr)); //use time to create random seed
	std::array<int, g_Elem> array;    //create array with random numbers uniformly distributed between g_min and g_max
	int range = g_max - g_min;
	for (int i = 0; i < g_Elem; i++)
	{
		seed = seed * 10007 + 24697;
		array[i] = g_min+seed % (range+1);
	}
    //printArray(array); // see initial array

	const std::array<int, g_Elem> constarray{ array }; //make a constant copy of the array we can use to make other copies of.

	std::array<int, g_Elem> array2{ constarray }; //array2 is now copy of array we can use
	std::array<int, g_Elem> array3{ constarray }; //array3 is now copy of array we can use

	

	Timer t; //create a timer object with a beginning time now

	sort(array);

	std::cout << t.elapsed() << " time was taken with sort.\n"; 
	//printArray(array); //check if correct

	t.reset(); //reset t

	preSort(array2);
    //printArray(array2); //debugging

	swapSort(array2);

	std::cout << t.elapsed() << " time was taken for swapSort with preSort.\n";
	//printArray(array2); //check if correct
	
	t.reset(); //reset t

	swapSort(array3);

	std::cout << t.elapsed() << " time was taken with just swapSort.\n";
    //printArray(array3); //check if correct
	
	
	return 0;
}


