#define _CRT_SECURE_NO_WARNINGS

//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 5, 9/17/19

#include <stdio.h>
#include <stdlib.h>

//#define _CRT_SECURE_NO_WARNINGS -> Project, Properties, C/C++, Preprocessor, Preprocessor Definitions
	//for some reason placing _CRT_... here does not work, but placing it in preprocessor settings works fine

//creating the Record struct to hold the information read in from the file
typedef struct
{
	int empID, ssn, position;
	float salary;
} Record;

int readRecordFile(char* filename, Record*** array);
void adjustSalaries(Record** employees, int n, int pos, float x); //int n = number of elements in the array
void freeRecordArray(Record*** array, int numElems);

/*main (summary):
*/
int main(void)
{
	Record** emp = NULL;
	int firstlinesize = readRecordFile("employeeprelabsix.csv", &emp); //function call to readRecordFile

	//if input file can't be opened terminate program
	if (firstlinesize == -1)
	{
		printf("\n*****INPUT FILE COULD NOT BE OPENED*****\n\n");
		return(-1);
	}

	//if memory can't be allocated terminate program
	if (firstlinesize == 0)
	{
		printf("\nMEMORY COULD NOT BE ALLOCATED (voidrecordarray)!!!\n");
		return(-1);
	}

	//printing the structs to the screen
	printf("\nID    Salary       SSN  Position\n");
	for (int a = 0; a < firstlinesize; a++)
	{
		printf("%2d %9.2f %9d %2d\n", emp[a]->empID, emp[a]->salary, emp[a]->ssn, emp[a]->position);
	}

	//calling adjustSalaries to give position 3 members a 5% raise
	adjustSalaries(emp, firstlinesize, 3, 1.05);

	//printing the adjusted salary structs to the screen
	printf("\n\n*****ADJUSTED SALARIES*****\nID    Salary       SSN  Position\n");
	for (int a = 0; a < firstlinesize; a++)
	{
		printf("%2d %9.2f %9d %2d\n", emp[a]->empID, emp[a]->salary, emp[a]->ssn, emp[a]->position);
	}

	freeRecordArray(&emp, firstlinesize); //function call to free the allocated memory
	return(0);
}

/*readRecordFile:
	reads the file
	creates an array of pointers to Records (using the read in size, allocate an array of pointers to Records)
		- allocate a Record for each Rocord in the file, and set it equal to the Record* (each allocated pointer)
	returns the size of the pointer array

	error codes:
	return(0) -> insufficient memory (if malloc fails at any point, you must free all the memory you've already allocated (don't cause a memory leak)
	return(-1) -> file can't be opened (make sure file is non Null)

	1. call fopen
	2. read int of how many records
	3. call malloc to allocate an array of pointers to Records
	4. use a loop to set each pointer equal to malloc(sizeof(Record))
	5. use a second loop to red in the records from the file (could be done in only one loop with memory allocation)
*/
int readRecordFile(char* filename, Record*** array)
{
	FILE* fptr = NULL;
	fptr = fopen(filename, "r"); //opening the random data file for reading, return (-1) if unsuccessful
	if (fptr == NULL) return (-1);

	int size = 0;
	fscanf(fptr, "%d\n", &size); //scanning in the integer to variable size from the file

	*array = malloc(size * sizeof(Record*)); //an array of pointers to Records, return (0) if unsuccessful malloc
	if (*array == NULL) return (0);

	//getting memory allocated for each pointer
	for (int i = 0; i < size; i++)
	{
		(*array)[i] = malloc(sizeof(Record));
		if ((*array)[i] == NULL)
		{
			printf("\n*****UNSUCCESSFUL ALLOCATION OF STRUCTS*****\n");
			for (int k = 0; k < i; k++)
			{
				free((*array)[k]);
			}
			return(0);
		}
	}

	for (int j = 0; j < size; j++)
	{
		fscanf(fptr, "%d,%f,%d,%d\n", &(*array)[j]->empID, &(*array)[j]->salary, &(*array)[j]->ssn, &(*array)[j]->position);

		/*
		((*array))[j]->empID = 10;
		((*array))[j]->salary = 20;   //another way to set the values without using scanf (note the one less level of indirection)
		((*array))[j]->ssn = 30;
		((*array))[j]->position = 40;
		*/
	}

	fclose(fptr);
	return(size);
}

/*adjustSalaries:
	multiplies the salary of each employee with position "pos" by x
	n is the number of elements in the array
*/
void adjustSalaries(Record** employees, int n, int pos, float x) //int n = number of elements in the array
{
	for (int i = 0; i < n; i++)
	{
		if (employees[i]->position == pos)
		{
			employees[i]->salary = ((employees[i]->salary) * (x));
		}
	}
}

/*freeRecordArray
	frees the array created by readRecordFile and sets the pointer in the calling program to null

	calls to malloc = size + 1
		- free each Record array first
		- then free the array of pointers
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
