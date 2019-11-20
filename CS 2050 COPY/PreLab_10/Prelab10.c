//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Prelab 10, 10/21/19

//Implementation of a Queue using a circular linked List

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodestruct {    
	int item;    
	struct nodestruct *next;
	} Node;
	
typedef struct {
	int size;
	Node * rear;
	} Queue;
	
Queue * initQueue(void);
int enqueue(int, Queue*);
int dequeue(Queue*, int*);
int getQsize(Queue*);
void freeQueue(Queue*);
void printQueue(Queue*);
	
int main(void)
{
	srand(time(NULL));
	Queue * q;
	q = initQueue(); 
	int input = 0; //used as the int inserted to enqueue, and the int returned from dequeue
	int error = 0; //checks error codes from enqueue and dequeue
	
	printf("Current Queue Size is %d\n", getQsize(q)); //empty queue operations
	printQueue(q);
	
	for(int i=0; i<3; i++) //3 enqueue
	{
		input = ((rand()%10)+1);
		error = enqueue(input, q);
		if(error == -1) printf("\n\n*****Unsuccessful Malloc*****\n\n");
		printf("Current Queue Size is %d\n", getQsize(q));
		printQueue(q);
	}
	
	for(int i=0; i<5; i++) //5 dequeue
	{
		error = dequeue(q, &input);
		if(error == -2) printf("*****Empty Queue; Nothing to Dequeue*****\n\n");
		
		else
		{
			printf("Integer removed from Queue was %d\n", input);
			printf("Current Queue Size is %d\n", getQsize(q));
			printQueue(q);
		}
	}
	
	for(int i=0; i<3; i++) //3 enqueue
	{
		input = ((rand()%10)+1);
		error = enqueue(input, q);
		if(error == -1) printf("\n\n*****Unsuccessful Malloc*****\n\n");
		printf("Current Queue Size is %d\n", getQsize(q));
		printQueue(q);
	}
	
	for(int i=0; i<4; i++) //4 dequeue
	{
		error = dequeue(q, &input);
		if(error == -2) printf("*****Empty Queue; Nothing to Dequeue*****\n\n");
		
		else
		{
			printf("Integer removed from Queue was %d\n", input);
			printf("Current Queue Size is %d\n", getQsize(q));
			printQueue(q);
		}
	}
	
	for(int i=0; i<3; i++) //3 enqueue
	{
		input = ((rand()%10)+1);
		error = enqueue(input, q);
		if(error == -1) printf("\n\n*****Unsuccessful Malloc*****\n\n");
		printf("Current Queue Size is %d\n", getQsize(q));
		printQueue(q);
	}
	
	freeQueue(q);
	q = NULL;
	return(0);	
}

/*initQueue:
	This function returns an empty queue; a Queue struct with a size 
	and pointer to the rear of the Queue
*/
Queue * initQueue(void)
{
	Queue * p;
	p = malloc(sizeof(Queue));
	if (p == NULL) printf("\n***Failed Malloc Initialization***\n"); //unsuccessful malloc
	p->size = 0; 
	p->rear = NULL; //pointing rear to NULL sice queue is empty
	return (p);
}

/*enqueue:
	This function places an integer at the rear of the queue
	
	return codes:
		-1: Unsuccessful malloc
		0: successful enqueue
*/
int enqueue(int inp, Queue * p)
{
	Node * newNode = malloc(sizeof(Node));
	if (newNode == NULL) return (-1); //unsuccessful malloc 
	p->size++; //incrementing the size variable since we are inserting a node
	newNode->item = inp; 
	
	if (p->rear == NULL) //the first insertion
	{
		p->rear = newNode;
		newNode->next = newNode; //point the newNode to itself
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

/*dequeue:
	This function removes the node at the front of the queue and stores
	the integer in the removed node in the passed int*
	
	return codes:
		-2: empty queue
		0: successful dequeue
*/
int dequeue(Queue * p, int * inp)
{
	if (p->rear == NULL) return(-2); //empty queue
	
	p->size--;
	*inp = p->rear->next->item; //item in the front of the queue
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

/*getQSize:
	This functions returns the size of the Queue stored in the Queue struct
*/
int getQsize(Queue * p)
{
	return(p->size);
}

/*freeQueue:
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

/*printQueue:
	This function prints off the current queue from front to rear-
*/
void printQueue(Queue * p)
{
	printf("Current Queue is: ");
	if (p->rear == NULL) printf("Empty Queue");
	else //non-empty queue
	{
		if (p->rear == p->rear->next) printf("%d ", p->rear->item); //1 in queue
		else //2 or more in queue
		{
			Node * temp = p->rear->next; //pointing temp to the front of the Queue
			while (temp != p->rear)
			{
				printf("%d ", temp->item);
				temp = temp->next;
			}
			printf("%d ", temp->item); //printing the item in the rear of the queue
		}
	}
	printf("\n\n");
}