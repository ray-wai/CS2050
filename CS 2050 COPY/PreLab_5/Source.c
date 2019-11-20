//Raymond Waidmann
//18157816, rcw5k2
//CS2050, PreLab 5, 9/12/19

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define _CRT_SECURE_NO_WARNINGS -> Project, Properties, C/C++, Preprocessor, Preprocessor Definitions
	//for some reason placing _CRT_... here does not work, but placing it in preprocessor settings works fine

void* createArray(int n, int elemsize); //allocate memory of any type
int getArraySize(void* array); //store the array size in array[-1]
void freeArray(void* array); //free the allocated memory (move the pointer back)

//creating the Record struct to hold the information read in from the file
typedef struct
{
	int empid, ssn, position;
	float salary;
} Record;

/* main (summary):
	The function opens a file where the first line is the size of the file, and the remainder of the file is employee data.
	Error check to ensure proper opening of the file and dynamically allocate the array based on the scanned in size.
	Error check to ensure proper memory allocation and initialize and print the rest of the array from the file data.
	Print the size of the array stored before the array, close the file, and free the mallocced memory. 
*/
int main(void)
{

	FILE* fptr =  NULL;
	fptr = fopen("rndmdata.txt", "r"); //opening the random data file for reading

	//error check to see if the file can be opened, display message and terminate if unsuccessful
	if (fptr == NULL) 
	{
		printf("\n*****INPUT FILE COULD NOT BE OPENED*****\n\n");
		return (-1); 
	}
	
	int size = 0; 
	fscanf(fptr, "%d", &size); //scanning in the integer to variable size from the file

	Record* voidrecordarray = createArray(size, sizeof(Record)); 

	//making sure memory was successfully malloced, terminating the program if unsuccessful
	if (voidrecordarray == NULL)
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (voidrecordarray)!!!\n");
		return (-1);
	}

	//simultaneously initializing the values of the array by scanning from the file to the allocated memory and printing the array to the screen
	printf("\nRecord Array is: \n%-8s%-10s%-10s%-10s\n", "EMP ID", "SSN", "Position", "Salary");
	for (int i = 0; i < size; i++)
	{
		fscanf(fptr, "%d%d%d%f", &voidrecordarray[i].empid, &voidrecordarray[i].ssn, &voidrecordarray[i].position, &voidrecordarray[i].salary);
		printf("%-8d%-10d%-10d%-10.2f\n", voidrecordarray[i].empid, voidrecordarray[i].ssn, voidrecordarray[i].position, voidrecordarray[i].salary);
	}
	puts("");

	//function call that finds the size of the created Record array stored before the array
	printf("Size of the array stored in array[-1] is %d\n", getArraySize(voidrecordarray));

	//closing the file and freeing the mallocced memory
	fclose(fptr);
	freeArray(voidrecordarray);

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