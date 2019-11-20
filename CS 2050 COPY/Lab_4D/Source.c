//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 4D, 9/10/19

//Shizeng's Talk Before Lab:
//10 random integers, boundary does not matter, you can initialize them in createarray or initialize them in main
//if you initialize in create array, initialize max there as well
//if you initialize in main, initialize max on main too

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void * createArray(int n, int elemsize); 
int getArraySize(void *array); 
void freeArray(void *array); 

/* main (summary):
	A function call to createArray malloccs memory for an int array, initializes the array randomly, and stores the size and max values before the returned pointer
	Error checking is done on the mallocced memory and the program is terminated if unsuccessful allocation occurs
	The size and max are printed to the screen via a function call to getArraySize and hardcoding respectively (Shizeng said this was ok)
	The array pointer is decremented back to before the max and size and the mallocced memory is freed
*/

int main(void)
{    
	srand(time(NULL)); // for random integers    
	int n = 10; // size of array    
	int* voidintarray = createArray(n, sizeof(int)); //C compilers do not requre casting

	//making sure memory was successfully malloced, terminating the program if unsuccessful
	if (voidintarray == NULL)
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (main)(voidintarray)!!!\n");
		return (-1);
	}

	printf("Size of the array is %d, and the maximum value in the array is %d\n", getArraySize(voidintarray), voidintarray[-2]);
	freeArray(voidintarray);
	return 0;
}

/* createArray:
	This function takes an integer number of elements and element size and mallocs the appropriate amount of memory plus an 
		additional 2 integer sizes of memory to store the size and max value before the array
	Error checking is done to ensure the memory was mallocced successfully
	The pointer is incremented and the size of the array is stored in what will become ARRAY[-1]
	The int array is initialized and printed to the screen
	The max of the array is found and stored in ARRAY[-2]
	The resulting void pointer is returned back to main

*/
void* createArray(int NUMELEMS, int ELEMSIZE)
{
	int* ARRAY = malloc((ELEMSIZE * NUMELEMS) + (2 * sizeof(int))); //2 * sizeof(int) -> one is for the max, the other is for the size. both are stored before the array
	if (ARRAY == NULL)
	{
		return (NULL); 
	}

	ARRAY++; //incrementing the pointer past where MAX will be stored since MAX is currently unknown
	ARRAY[0] = NUMELEMS; //initializing memory one chunk before the returned array to the size
	ARRAY++; //incrementing the pointer to where the array will actually begin

	//simultaneously initializing the values of the array randomly and printing the array to the screen
	printf("\nInt Array is: ");
	for (int i = 0; i < NUMELEMS; i++)
	{
		ARRAY[i] = ((rand() % 100) + 1);
		printf("%d, ", ARRAY[i]);
	}
	puts("");

	//finding the max
	int MAX = ARRAY[0];
	for (int j = 1; j < NUMELEMS; j++)
	{
		if (ARRAY[j] > MAX)
		{
			MAX = ARRAY[j];
		}
	}
	ARRAY[-2] = MAX; //storing the max before the array and before the size
	return (void*)(ARRAY); 
}

/* getArraySize:
	This function returns the size of the array in ARRAY[-1] to main (before the array) which was initialized in the createArray function 
	Casting is required due to the void* function prototype
*/
int getArraySize(void* ARRAY)
{
	return(((int*)ARRAY)[-1]);
}

/* freeArray:
	This function decrements the pointer to the array back so that it includes the size and max value 
	of the array (ARRAY[-1], ARRAY[-2]) and then frees all of the mallocced memory. It is casted as an int
	so that the pointer arithmetic works correctly for ANY type of array passed to this function.
*/
void freeArray(void* ARRAY)
{
	free(((int*)ARRAY) - 2);
}