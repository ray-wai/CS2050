//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 10, 10/22/19

//Implementation of a Queue using a circular linked List without dummy nodes

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodestruct {    
	int item;    
	struct nodestruct *next;
	} Node;
	
typedef struct {
	int size, sum;
	Node * rear;
	} Queue;
	
Queue * initQueue(void);
int enqueue(int, Queue*);
int dequeue(Queue*, int*);
int getSum(Queue*);
void freeQueue(Queue*);

/*initQueue; O(1) complexity:
	This function returns an empty queue; a Queue struct with an integer size and sum, 
	and a pointer to the rear of the Queue
*/
Queue * initQueue(void)
{
	Queue * p;
	p = malloc(sizeof(Queue));
	if (p == NULL) printf("\n***Failed Malloc Initialization***\n"); //unsuccessful malloc
	p->size = 0; 
	p->sum = 0;
	p->rear = NULL; //pointing rear to NULL sice queue is empty (no dummy nodes)
	return (p);
}

/*enqueue; O(1) complexity
	This function places an integer at the rear of the queue. This function also 
	increments the size and sum members in the Queue pointer based on the integer about 
	to be enqueued
	
	return codes:
		-1: Unsuccessful malloc
		0: successful enqueue
*/
int enqueue(int inp, Queue * p)
{
	Node * newNode = malloc(sizeof(Node));
	if (newNode == NULL) return (-1); //unsuccessful malloc 
	p->size++; 
	p->sum += inp; 
	newNode->item = inp; 
	
	if (p->rear == NULL) //the first insertion
	{
		p->rear = newNode;
		newNode->next = newNode; //point the newNode to itself (maintain circular list even with just one node)
		return(0);
	}
	
	else //1 or more items already queued
	{
		newNode->next = p->rear->next; //pointing newNode to the front node
		p->rear->next = newNode; //pointing rear node to the new node
		p->rear = newNode; //moving the rear pointer to the new rear of the queue
		return(0);
	}
}

/*dequeue; O(1) complexity:
	This function removes the node at the front of the queue and stores
	the integer in the removed node in the passed int*. This function decrements the size
	and sum members based on the integer about to be dequeued
	
	return codes:
		-2: empty queue
		0: successful dequeue
*/
int dequeue(Queue * p, int * inp)
{
	if (p->rear == NULL) return(-2); //empty queue
	
	p->size--;
	*inp = p->rear->next->item; //item in the front of the queue
	p->sum -= (*inp);  
	if(p->rear == p->rear->next) //only one item in the queue
	{
		free(p->rear);
		p->rear = NULL;
		return(0);
	}
	
	else //one or more items in queue
	{
		Node * temp;
		temp = p->rear->next; //temp is front of Queue
		p->rear->next = temp->next; //pointing rear to node second from front
		free(temp); 
		return(0);
	}
}

/*getSum; O(1) complexity:
	This funtion returns the sum of all the current items in the Queue
*/
int getSum(Queue * p)
{
	return(p->sum);
}

/*freeQueue; O(n) complexity:
	This function frees all of the malloced nodes using a temp pointer to be
	sure not to access any memory after is has been freed
*/
void freeQueue(Queue * p)
{
	Node* temp;
	while(p->rear != p->rear->next) //while 2 or more nodes in queue
	{
		temp = p->rear->next; //front of Queue
		p->rear->next = temp->next; //pointing rear to node second from front
		free(temp);
	}
	free(p->rear); //freeing the last node
	p->rear = NULL;	
	printf("Queue has been freed\n");
}