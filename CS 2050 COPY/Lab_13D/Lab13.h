//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 12, 11/5/19

//Implementation of a priority queue with an array that supports DeQueue O(1) and
//findIdx (Binary search O(log(n))) 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int arraySize;// the maximum size of the sorted array (constant value)
	int availableIdx;// nextavailable index in the sorted array; this is literally just the size of the current array
	int *sortedArray;// the sorted array
} PQueue;

PQueue* initPQ(int);
int insertPQ(PQueue*, int); 
int DeQueue(PQueue*, int*); 
int findIdx(PQueue*, int); 
void freePQ(PQueue*);
void printPQ(PQueue*);