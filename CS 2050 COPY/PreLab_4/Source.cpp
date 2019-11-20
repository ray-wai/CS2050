//Raymond Waidmann
//18157816, rcw5k2
//CS2050 PreLab 4 9/6/19

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* createArray(int n, int elemsize); //allocate memory of any type
int getArraySize(void* array); //store the array size in array[-1]
void freeArray(void* array); //free the allocated memory (move the pointer back)

int main(void)
{
	srand(time(0)); // Use current time as seed for random generator 
	int size1 = ((rand() % 10) + 10);
	int size2 = ((rand() % 10) + 10);
	int size3 = ((rand() % 10) + 10);
	int size4 = ((rand() % 10) + 10);
	printf("\nThe sizes of the arrays are %d, %d, %d, %d\n", size1, size2, size3, size4);

	//the returned void* from the function call is casted to the proper type for each function call
	int* voidintarray = (int*)createArray(size1, sizeof(int)); 
	float* voidfloatarray = (float*)createArray(size2, sizeof(float));
	double* voiddoublearray = (double*)createArray(size3, sizeof(double));
	char* voidchararray = (char*)createArray(size4, sizeof(char));

	//making sure memory was successfully malloced, terminating the program if unsuccessful
	if (voidintarray == NULL) 
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (voidintarray)!!!\n");
		return (-1);
	}

	if (voidfloatarray == NULL) 
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (voidfloatarray)!!!\n");
		return (-1);
	}

	if (voiddoublearray == NULL) 
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (voiddoublearray)!!!\n");
		return (-1);
	}

	if (voidchararray == NULL) 
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (voidchararray)!!!\n");
		return (-1);
	}

	//simultaneously initializing the values of the arrays randomly for the appropriate type and printing the arrays to the screen
	printf("\nInt Array is: ");
	for (int i = 0; i < size1; i++) 
	{
		voidintarray[i] = ((rand() % 10) + 1);
		printf("%d, ", voidintarray[i]);
	}
	puts("");
	printf("Size of the array is %d\n", getArraySize(voidintarray));

	printf("\nFloat Array is: ");
	for (int j = 0; j < size2; j++) 
	{
		voidfloatarray[j] = ((rand() % 10) + 1);
		printf("%.2f, ", voidfloatarray[j]);
	}
	puts("");
	printf("Size of the array is %d\n", getArraySize(voidfloatarray));

	printf("\nDouble Array is: ");
	for (int k = 0; k < size3; k++) 
	{
		voiddoublearray[k] = ((rand() % 10) + 1);
		printf("%.2f, ", voiddoublearray[k]);
	}
	puts("");
	printf("Size of the array is %d\n", getArraySize(voiddoublearray));

	printf("\nChar Array is: ");
	for (int l = 0; l < size4; l++)
	{
		int r = rand() % 26;
		voidchararray[l] = 'a' + r;
		printf("%c, ", voidchararray[l]);
	}
	puts("");
	printf("Size of the array is %d\n", getArraySize(voidchararray));

	//freeing the malloced memory
	freeArray(voidintarray);
	freeArray(voidfloatarray);
	freeArray(voiddoublearray);
	freeArray(voidchararray);
	
	return(0);
}

/* createArray:
	This function takes an integer number of elements and element size and mallocs the appropriate amount of memory plus an additional integer size of bytes to store the size.
	The resulting void pointer is incremented after storing the size in array[0] and is returned back to main.
	It should be noted that this function can malloc memory for ANY type, as long as the returned void pointer is casted to the appropriate type in main.
*/
void* createArray(int NUMELEMS, int ELEMSIZE)
{
	int* ARRAY = (int*)malloc((ELEMSIZE * NUMELEMS) + sizeof(int));
	ARRAY[0] = NUMELEMS;
	ARRAY++;
	return (void*)(ARRAY);
}

/* getArraySize:
	This function returns the size of the array store before the array in function createArray
*/
int getArraySize(void* ARRAY)
{
	return(((int*)ARRAY)[-1]);
}

/* freeArray:
	This function decrements the pointer to the array back so that it includes the size of the array, and then frees all of the mallocced memory
*/
void freeArray(void* ARRAY)
{
	free(((int*)ARRAY) - 1);
}