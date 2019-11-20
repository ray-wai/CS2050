#include "Lab13.h"

/*initPQ: O(1);
	This function initializes an array of size sz and creates a PQueue pointer
	that contains a size element and a pointer to the initialized array
*/
PQueue * initPQ(int sz)
{
	int * array = malloc(sizeof(int)*sz);
	PQueue * p;
	p = malloc(sizeof(PQueue));
	p->arraySize = sz;
	p->availableIdx = 0;
	p->sortedArray = array;
	return(p);
}

/*insertPQ: O(n);
	This function takes a random int and explicitly inserts it into the array
	in sorted order. 
	
	Return codes:
	-1: unsuccessful insertion (full array)
	0: successful insertion
*/
int insertPQ(PQueue * p, int new)
{
	if (p->availableIdx == p->arraySize) return(-1);
	int i = 0;
	while(i < (p->availableIdx) && (p->sortedArray)[i] < new) i++; //finding the index where the key is greater than new
	for (int j = p->availableIdx; j > i; j--) (p->sortedArray)[j] = (p->sortedArray)[j-1]; //shifting greater keys over an index
	(p->sortedArray)[i] = new; //inserting the new key
	p->availableIdx++;
	return(0);
}

/*DeQueue: O(1);
	This function deletes the largest key currently in the priority queue	
	and returns it to main by reference
	
	return codes:
	-1: empty list (nothing to delete)
	0: successful deletion
*/
int DeQueue(PQueue * p, int * a)
{
	if (p->availableIdx == 0) return (-1);
	else{
	*a = (p->sortedArray)[(p->availableIdx)-1];
	(p->sortedArray)[(p->availableIdx-1)] = 0; //it really doesn't matter what number this is anyways, but 0 will suffice as a "null" integer...
	p->availableIdx--;
	return(0);
	}
}

/*findIdx: O(log(n));
	This function uses a binary search method to see if the key is in the current queue
	If the key is found, it returns the index where that key was found 
	
	Return codes:
	-1: key not found in queue, or empty list
	any other integer: key found in queue at that index
*/
int findIdx(PQueue * p, int key)
{
	int low = 0;
	int high = (p->availableIdx)-1;
	while (low <= high)
	{
		int mid = (low + high)/2;
		if (key > (p->sortedArray)[mid]) low = mid + 1;
		if (key < (p->sortedArray)[mid]) high = mid - 1;
		if (key == (p->sortedArray)[mid]) return(mid);
	}
	return(-1);
}

/*freePQ: O(1);
	This function frees all the allocated memory
*/
void freePQ(PQueue * p)
{
	free(p->sortedArray);
	free(p);
	printf("\nQueue has been freed\n");
}

/*printarray: O(n);
	This function prints off the current array
*/
void printPQ (PQueue * p)
{
	for (int i = 0; i < p->availableIdx; i++) printf("%d ", (p->sortedArray)[i]);
	puts("");
}