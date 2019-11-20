//Raymond Waidmann
//CS 2050 Prelab 3
//18157816, rcw5k2

//creating a program that calls functions to allocate memory via malloc to create an int array with initialization,
//and to create an array of unknown type without initialization

#include <stdio.h>
#include <stdlib.h>

int* createIntArray(int size, int init); //function proptotypes
void * createArray(int numElems, int elemSize);

int main(void)
{
	int* intarray; //creating a pointer to an integer array
	int n = 100; //size of the array
	intarray = createIntArray(n, 0); //function call
	if (intarray == NULL)
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (intarray)!!!\n"); //making sure memory was successfully malloced
		return (-1); //terminating program if memory allocation fails
	}

	for (int i = 0; i < n; i++) //this for loop loops through the allocated array and prints the initialized values
	{
		printf("%d ", intarray[i]);
		if (i % 10 == 9) //since size is 100, every 10 values put a new line so we get a nice 10x10 output
		{
			puts("");
		}
	}

	int* voidintarray;
	float* floatarray; //initializing the different types of arrays
	char* chararray;

	voidintarray = /*(int*)*/createArray(n, sizeof(int)); //calling the create array function, the returned void* is casted to the proper type int*
	if (voidintarray == NULL)
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (voidintarray)!!!\n"); //making sure memory was successfully malloced
		return (-1); //terminating program if memory allocation fails
	}

	else
	{
		printf("SUCCESSFUL ALLOCATION ON VOINDINTARRAY\n"); //if allocation was successful, display this message
	}

	floatarray = (float*)createArray(n, sizeof(float)); //see comments for lines 38-48
	if (floatarray == NULL)
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (floatarray)!!!\n"); 
		return (-1); 
	}

	else
	{
		printf("SUCCESSFUL ALLOCATION ON FLOATARRAY\n");
	}

	chararray = (char*)createArray(n, sizeof(char)); //see comments for lines 38-48
	if (chararray == NULL)
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (chararray)!!!\n"); 
		return (-1); 
	}

	else
	{
		printf("SUCCESSFUL ALLOCATION ON CHARARRAY\n");
	}

	free(intarray);
	free(voidintarray); //freeing the malloced memory
	free(floatarray);
	free(chararray);
}

int* createIntArray(int SIZE, int INIT)
{
	int* INTARRAY = (int*)malloc(sizeof(int) * SIZE); //mallocing the memory, casting malloc return type to int
	for (int i = 0; i < SIZE; i++) //initializing the array to the value passed to the function
		{
			INTARRAY[i] = INIT;
		}
	return (INTARRAY); //returning the pointer to main
}

void* createArray(int NUMELEMS, int ELEMSIZE)
{
	void* ARRAY = malloc(ELEMSIZE * NUMELEMS); //mallocing a void* to the specified size with correct number of elements
	return (ARRAY); //returning this void* to main, it will then be casted in main to be the appropriate type (int*, float*, char*)
}