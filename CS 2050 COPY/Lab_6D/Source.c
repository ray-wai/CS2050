#define _CRT_SECURE_NO_WARNINGS

//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 6, 9/24/19

#include <stdio.h>
#include <stdlib.h>

//creating the Record struct to hold the information read in from the file
typedef struct
{
	int empID, age;
	float salary;
} Record;

int readRecordFile(char* filename, Record*** array);
int findSalary(Record** array, int salaryLow, int salaryHigh, int size);
void freeRecordArray(Record*** array, int numElems);

/*main (summary):
	This function opens a file and reads the first line containing the file size.
	Then, the program allocates an array of pointers, and allocates a struct for each pointer. 
	The data from the file is scanned into the structs. If the file cant be opened or malloc fails, the program terminates.
	Use a function call to test to see how many salaries in the structs are between a given range.
	Use a function call to free all of the mallocced memory. 
*/
int main(void)
{
	Record** emp = NULL;
	int firstlinesize = readRecordFile("employee.csv", &emp); //function call to readRecordFile

	//if input file can't be opened terminate program
	if (firstlinesize == -1)
	{
		printf("\n*****INPUT FILE COULD NOT BE OPENED*****\n\n");
		return(-1);
	}

	//if memory can't be allocated terminate program
	if (firstlinesize == 0)
	{
		printf("\n*****MEMORY COULD NOT BE ALLOCATED*****\n\n");
		return(-1);
	}

	int Low = 10000;
	int High = 50000;
	int between = findSalary(emp, Low, High, firstlinesize); //function call to find number of salaries between 10000 and 50000
	printf("\nThe number of employees with salaries between $10000 and $50000 is %d\n\n", between);

	freeRecordArray(&emp, firstlinesize); //function call to free the allocated memory
	return(0);
}

/*readRecordFile:
	error codes:
	return(0) -> insufficient memory (malloc fails)
	return(-1) -> file can't be opened (file* = NULL)

	1. call fopen
	2. read int of how many records from first line of file
	3. call malloc to allocate an array of pointers to Records
	4. use a loop to set each pointer equal to malloc(sizeof(Record)); allocate a struct for each pointer
	5. use a second loop to read in the records from the file into the allocated structs
	6. return the size read from the first line of the file back to main
*/
int readRecordFile(char* filename, Record*** array)
{
	FILE* fptr = NULL;
	fptr = fopen(filename, "r"); //opening the random data file for reading, return (-1) if unsuccessful
	if (fptr == NULL) return (-1);

	int size = 0;
	fscanf(fptr, "%d\n", &size); //scanning in the integer to variable size from the file

	*array = malloc(size * sizeof(Record*)); //an array of pointers to Records, return (0) if unsuccessful malloc of the pointer array
	if (*array == NULL) return (0);

	//getting memory allocated for each pointer
	for (int i = 0; i < size; i++)
	{
		(*array)[i] = malloc(sizeof(Record));

		//if malloc fails at any point when allocating structs, use a for loop to free all the memory previously allocated, then free the pointer array and set the pointer to NULL
		if ((*array)[i] == NULL) 
		{
			printf("\n*****UNSUCCESSFUL ALLOCATION OF STRUCTS*****\n");
			for (int k = 0; k < i; k++)
			{
				free((*array)[k]);
			}
			free(*array); //freeing the pointer array
			*array = NULL;
			return(0);
		}
	}

	for (int j = 0; j < size; j++)
	{
		fscanf(fptr, "%d,%f,%d\n", &(*array)[j]->empID, &(*array)[j]->salary, &(*array)[j]->age); //scanning in the file data into the structs
	}

	fclose(fptr);
	return(size);
}

/*findSalary:
	This function loops through the salary member of each struct and checks to see if it is between 10000-50000
	If the salary is within the range, increment a counter variable and return the counter to main after the loop is complete
*/
int findSalary(Record** array, int salaryLow, int salaryHigh, int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i]->salary > salaryLow && array[i]->salary < salaryHigh)
		{
			count++;
		}
	}
	return (count);
}

/*freeRecordArray
	frees the array created by readRecordFile and sets the pointer in the calling program to null

	total calls to malloc = size + 1
		- free each Record array first (size)
		- then free the array of pointers (+1)
*/
void freeRecordArray(Record*** array, int numElems)
{
	for (int i = 0; i < numElems; i++)
	{
		free((*array)[i]); //freeing all the structs
	}
	free(*array); //freeing the pointer array
	*array = NULL;
}
