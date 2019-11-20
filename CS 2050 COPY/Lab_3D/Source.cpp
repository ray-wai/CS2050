//Raymond Waidmann
//CS 2050, Lab 3D
//18157816, rcw5k2

# include<stdio.h>
# include <stdlib.h>
# include <time.h>

void computeInOut(int arr[], int size, int lowBoundary, int highBoundary, int* inPtr, int* outPtr);
void* createArray(int elemSize, int elemNumber);

/* MAIN (SUMMARY):
  This program creates an integer array by using a function call to malloc memory. Error checking is done to ensure sucessful allocation
  The array is initialized with random numbers between 1-10. The resulting array is printed to the screen.
  Then, another function is called to compute which values of the array are and are not within a specified boundary.
  The inlier and outlier results from the second function call are printed to the screen and the allocated memory is freed.
*/
int main(void) 
{    
	srand(time(0)); // Use current time as seed for random generator 
	int size = 10, lowBoundary = 3, highBoundary = 6, inliers = 0, outliers = 0;    
	int* voidintarray = (int*)createArray(size, sizeof(int)); //the returned void* from the function call is casted to the proper type int*

	if (voidintarray == NULL) //making sure memory was successfully malloced, terminating the program if unsuccessful
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (voidintarray)!!!\n"); 
		return (-1); 
	}

	printf("\nArray is: ");
	for (int i = 0; i < size; i++) //simultaneously initializing the values of the array randomly between 1-10 and printing the array to the screen
	{
		voidintarray[i] = ((rand() % 10)+1);
		printf("%d, ", voidintarray[i]);
	}
	puts("");

	computeInOut(voidintarray, size, lowBoundary, highBoundary, &inliers, &outliers); //passing the address of inliers and outliers so their values can be edited by reference
	printf("Array has %d inliers and %d outliers\n", inliers, outliers);
	free(voidintarray); 
	return 0;
}

/* createArray:
	This function takes an integer number of elements and element size and mallocs the appropriate amount of memory.
	The resulting void pointer is returned back to main.
	It should be noted that this function can malloc memory for ANY type, as long as the returned void pointer is casted to the appropriate type in main.
*/
void* createArray(int NUMELEMS, int ELEMSIZE)
{
	void* ARRAY = malloc(ELEMSIZE * NUMELEMS); 
	return (ARRAY); 
}

/* computeInOut:
	This function takes the initialized array, size of the array, lower and upper boundaries, and two pointers to the number of inliers and outliers.
	The function then loops through the array and increments variables inliers and outliers by reference based on if the array value is between 
		the specified lower and upper boundaries.
*/
void computeInOut(int ARRAY[], int SIZE, int LOW, int HIGH, int* IN, int* OUT)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (LOW < ARRAY[i] && ARRAY[i] < HIGH) (*IN)++; //if the value is greater than the lower boundary AND smaller than the higher boundary
		else (*OUT)++;
	}
}