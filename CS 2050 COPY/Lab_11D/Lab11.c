//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 11, 10/29/19

//Implementation of a priority Queue using a standard linked list with a single dummy at the beginning

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodestruct {    
	int key;
	float priority;   
	struct nodestruct *next;
	} Node;
	
typedef struct {
	int size;
	Node *front, *rear; //we will not utilize the front* in this implementation
	} PQueue;

PQueue * initPQ(); 
int insertPQ(int, float, PQueue *); 
int deleteMinPQ(PQueue *, int *);
void reInitPQ(PQueue *); 
void freePQ(PQueue *); 
void printPQ(PQueue *);

/*initPQ: O(1);
	This function returns an empty priority queue with rear pointing to a dummy node
*/
PQueue * initPQ(void) 
{
	PQueue * p;
	p = malloc(sizeof(PQueue));
	if (p == NULL) printf("\n***Failed Malloc Initialization***\n"); //unsuccessful malloc
	
	Node * q; //dummy
	q = malloc(sizeof(Node));
	if (q == NULL) printf("\n***Failed Malloc Initialization***\n"); //unsuccessful malloc
	q->key = 0; //dummy key = 0
	
	p->size = 0; 
	p->rear = q; //pointing rear to dummy
	p->front = NULL; //we will not be using the front* in this implementation
	q->next = NULL; //pointing dummy to NULL since queue is empty
	return (p);
}

/*insertPQ: O(n);
	This function inserts a new node into the queue with an integer key and float priority in ascending order
	
	Return codes:
		0: successful insertion
		-1: failed malloc
*/
int insertPQ(int inp, float pri, PQueue * p)
{
	Node * newNode = malloc(sizeof(Node));
	if (newNode == NULL) return (-1); //unsuccessful malloc 
	p->size++; 
	newNode->key = inp; 
	newNode->priority = pri;
	
	if (p->rear->next == NULL) //the first insertion
	{
		p->rear->next = newNode;
		newNode->next = NULL; //point the newNode to NULL since it's at the end of the queue
		return(0);
	}
																												
	else //1 or more keys already queued
	{
		Node * temp;
		temp = p->rear; //dummy
		
		while(temp->next != NULL && temp->next->priority < pri) //it is worth noting the order of these conditions is important, 
																//if they are reversed and a key needs to be inserted at the end of queue,
																//temp->next->priority does not exist and the program has a runtime error
		{
			temp = temp->next; //moving temp to node previous to where newnode is inserted
		}
		
		newNode->next = temp->next; //if insertion at the end of the queue, temp->next is simply NULL
		temp->next = newNode;
		return(0);
	}
}

/*deleteMinPQ: O(1); 
	This function deletes the node with the lowest priority and returns it by reference to main;
	The node with the lowest priority os the one the dummy points to, so we simply remove the first non-dummy node

	Return codes:
		0: successful delete max
		-1: empty queue
*/
int deleteMinPQ(PQueue * p, int * inp)
{
	Node * q = p->rear;
	if (q->next == NULL) return(-1); //empty queue
	else
	{
		p->size--;
		*inp = q->next->key;
		
		if(q->next->next == NULL) //1 key in queue
		{
			free(q->next);
			q->next = NULL;
		}
		
		else //2 or more keys in queue
		{
			Node * temp = q->next; //first non-dummy node
			q->next = q->next->next; //pointing dummy to node #2
			free(temp);
		}
		return(0);
	}
}

/*reInitPQ: O(n);
	This function reinits an existing priority queue as an empty priority queue
*/
void reInitPQ(PQueue * p)
{
	Node* tempdummy = p->rear;
	Node* temp;
	p->rear = p->rear->next;
	while(p->rear != NULL) //if the node is non-null
	{
		temp = p->rear; 
		p->rear = p->rear->next;
		free(temp); //free the node previous stored in temp
	}
	p->size = 0;
	p->rear = tempdummy; //pointing rear back to the dummy node
	tempdummy->next = NULL; //pointing the dummy to NULL since queue is empty
	printf("\n\nQueue has been reinitialized\n");
}

/*freePQ: O(n);
	This function frees all of the memory allocated for the queue
*/
void freePQ(PQueue * p)
{
	Node* temp;
	while(p->rear != NULL) //if the node is non-null
	{
		temp = p->rear; 
		p->rear = p->rear->next;
		free(temp); //free the node previous stored in temp
	}
	printf("\n\nQueue has been freed\n");
}

/*printPQ: O(n);
	This function prints the current Queue to the screen
*/
void printPQ(PQueue * p)
{
	Node * q = p->rear->next;
	if (q == NULL) printf("\nEMPTY QUEUE\n");
	else //non-empty queue
	{
		printf("\nCurrent PQ is: ");
		while(q->next != NULL)
			{
				printf("Key %d with priority %.2f --> ", q->key, q->priority);
				q = q->next;
			}
		printf("Key %d with priority %.2f --> NULL", q->key, q->priority); //printing the last key in queue
	}
}