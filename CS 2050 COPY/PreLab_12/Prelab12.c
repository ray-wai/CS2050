//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Prelab 12, 11/4/19

//Implementation of a priority queue with an array that supports deleteMax O(1) and
//isInPQ (Binary search O(log(n))) 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int size;
	float * arr;
	} PQueue;

PQueue * initPQ(int); 
int insertPQ(float, PQueue *); //int error code????
void printarray(PQueue *);
int deleteMaxPQ (PQueue *, float *); 
int getSizePQ (PQueue *); 
int isInPQ(float, PQueue *);
void freePQ(PQueue *); //is this correct ????

int main (void)
{
	srand(time(NULL));
	PQueue * pq;
	pq = initPQ(25); //initializing an array with 25 floats
	float deput = 0;
	int error = 0;
	
	//NOTE: EMPTY QUEUE OPERATION OF DELETEMAX AND ISINPQ ARE TESTED AND WORK CORRECTLY
	
	for (int i = 0; i < 33; i++) 
	{
		float find = (float)rand()/(float)(RAND_MAX/1); //random float
		error = insertPQ(find, pq); 
		if (error == 0) printf("*****UNSUCCESSFUL INSERTION*****\n");
		printarray(pq);
		if (i%5 == 4)
		{
			error = deleteMaxPQ(pq, &deput); 
			if (error == 0) printf("\n\n*****UNSUCCESSFUL DELETION; EMPTY LIST*****\n\n");
			else printf("SUCCESSFUL DELETION, FLOAT REMOVED WAS %.2f\n", deput);
			printf("Current size of queue is %d\n", getSizePQ(pq));
			
			error = isInPQ(find, pq);
			if (error == 1) printf("%.2f was found in the PQ\n", find);
			else printf("%.2f was not found in the PQ\n", find);
		}
	}
	freePQ(pq);
	pq = NULL;
	return(0);
}

/*initPQ: O(1);
	This function initializes an array of size sz and creates a PQueue pointer
	that contains a size element and a pointer to the initialized array
*/
PQueue * initPQ(int sz)
{
	float * array = malloc(sizeof(float)*sz);
	PQueue * p;
	p = malloc(sizeof(PQueue));
	p->size = 0;
	p->arr = array;
	return(p);
}

/*insertPQ: O(n);
	This function takes a random floating point number and explicitly inserts it into the array
	in sorted order. 
	
	Return codes:
	0: unsuccessful insertion (full array)
	1: successful insertion
*/
int insertPQ(float new, PQueue * p)
{
	if (p->size == 25) return(0);
	int i = 0;
	while(i < (p->size) && (p->arr)[i] < new) i++; //finding the index where the key is greater than new
	for (int j = p->size; j > i; j--) (p->arr)[j] = (p->arr)[j-1]; //shifting greater keys over an index to make room for new
	(p->arr)[i] = new; //inserting the new key
	p->size++;
	return(1);
}

/*printarray: O(n);
	This function prints off the current array
*/
void printarray (PQueue * p)
{
	for (int i = 0; i < p->size; i++) printf("%.2f ", (p->arr)[i]);
	puts("");
}

/*deleteMaxPQ: O(1);
	This function deletes the largest key currently in the priority queue	
	and returns it to main by reference
	
	return codes:
	0: empty list (nothing to delete)
	1: successful deletion
*/
int deleteMaxPQ(PQueue * p, float * a)
{
	if (p->size == 0) return (0);
	else{
	*a = (p->arr)[(p->size)-1];
	(p->arr)[(p->size-1)] = -1; //a number not in the range of input values
	p->size--;
	return(1);
	}
}

/*getSizePQ: O(1);
	This function returns the current number of items in the priority queue
*/
int getSizePQ (PQueue * p)
{
	return (p->size);
}

/*isInPQ: O(log(n));
	This function uses a binary search method to see if the key is in the current queue
	
	Return codes:
	0: key not found in queue, or empty list
	1: key found in queue
*/
int isInPQ(float key, PQueue * p)
{
	int low = 0;
	int high = (p->size)-1;
	while (low <= high)
	{
		int mid = (low + high)/2;
		if (key > (p->arr)[mid]) low = mid + 1;
		if (key < (p->arr)[mid]) high = mid - 1;
		if (key == (p->arr)[mid]) return(1);
	}
	return(0);
}

/*freePQ: O(1);
	This function frees all the allocated memory
*/
void freePQ(PQueue * p)
{
	free(p->arr);
	free(p);
	printf("\nQueue has been freed\n");
}


/* Random stuff from lectures and other code snips i'm not using in this implementation

//  *****iterative binary search (this implementation is more appropriate given the function prototypes*****
booleanmember(intorderedArray[ ], intfirst, intlast, intquery)
{
	intmid;
	while (first <= last) {
		mid = (first+last)/2;
		if (query > orderedArray[mid]) {    // query value is in the 2ndhalf of array
		first = mid+1;
	}
	else if (query < orderedArray[mid]) {    // query value is in the 1sthalf of array
		last = mid-1;
	}else {             // query value is found
		return true;
	}
	}
	return false;      
} 


//  *****recursive binary search in lecture (not using this in this implementation)*****
booleanmember(intorderedArray[ ], intfirst, intlast, intquery)
	{
		if  (first > last)  {
			return false;
		}
		intmid = (first+last)/2;
		if (query > orderedArray[mid]) {
			return member(orderedArray, mid+1, last, query);
		}
		else if (query < orderedArray[mid]) {
			return member(orderedArray, first, mid-1, query);
		}
		return true;     
	} 


//  *****recursive implementation that i tried but couldn't get to work*****
int binarySearch(float arr[], int low, int high, int key)
{
	int mid = (low + high)/2;
	if (arr[mid] == key) return (1);
	if (arr[mid] > key) return (binarySearch(arr, low, mid-1, key));
	return (binarySearch(arr, mid+1, high, key));
	return(0);
}
*/