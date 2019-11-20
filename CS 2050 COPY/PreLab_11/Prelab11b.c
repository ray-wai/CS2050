//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Prelab 11b, 10/29/19

//Implementation of a priority Queue using a linked list with two dummies at either end in a doubly linked list
//deleteMax and deleteMin are both O(1) using rear and front pointers within the PQueue struct

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodestruct {    
	int item;
	float priority;   
	struct nodestruct *next, *back;
	} Node;
	
typedef struct {
	int size;
	Node *rear, *front;
	} PQueue;

PQueue * initPQ(); 
int insertPQ(int, float, PQueue *); 
int deleteMaxPQ(PQueue *, int *);
int deleteMinPQ(PQueue *, int *);
int getSizePQ(PQueue *); 
void reInitPQ(PQueue *); 
void freePQ(PQueue *); 
void printPQ(PQueue *);

int main (void)
{
	srand(time(NULL));
	PQueue * pq;
	pq = initPQ(); 
	
	printf("Current Queue Size is %d\n", getSizePQ(pq)); //empty queue operations
	printPQ(pq);
	
	int input = 0;
	float rank = 0;
	int error = 0;
	
	for (int i = 0; i<4; i++) //4 enqueue
	{
		input = ((rand()%9)+1);
		rank = (float)rand()/(float)(RAND_MAX/1);
		error = insertPQ(input, rank, pq);
		if (error == -1) break;
		printf("\nItem Insertion, Current Queue Size is %d\n", getSizePQ(pq));
		printPQ(pq);
	}
	
	for(int i=0; i<3; i++) //6 dequeue
	{
		error = deleteMinPQ(pq, &input);
		if(error == -1) printf("*****Empty Queue; Nothing to Dequeue*****\n");
		else
		{
			printf("\nItem removed from Queue was %d\n", input);
			printf("Current Queue Size is %d\n", getSizePQ(pq));
			printPQ(pq);
		}
		
		error = deleteMaxPQ(pq, &input);
		if(error == -1) printf("*****Empty Queue; Nothing to Dequeue*****\n");
		else
		{
			printf("\nItem removed from Queue was %d\n", input);
			printf("Current Queue Size is %d\n", getSizePQ(pq));
			printPQ(pq);
		}
	}
	
	for (int i = 0; i<4; i++) //4 enqueue
	{
		input = ((rand()%9)+1);
		rank = (float)rand()/(float)(RAND_MAX/1);
		error = insertPQ(input, rank, pq);
		if (error == -1) break;
		printf("\nItem Insertion, Current Queue Size is %d\n", getSizePQ(pq));
		printPQ(pq);
	}
	
	reInitPQ(pq);
	
	for (int i = 0; i<4; i++) //4 enqueue
	{
		input = ((rand()%9)+1);
		rank = (float)rand()/(float)(RAND_MAX/1);
		error = insertPQ(input, rank, pq);
		if (error == -1) break;
		printf("\nItem Insertion, Current Queue Size is %d\n", getSizePQ(pq));
		printPQ(pq);
	}
	
	freePQ(pq);
	pq = NULL;
	return(0);
}

/*initPQ: O(1);
	This function returns an empty priority queue
*/
PQueue * initPQ(void) 
{
	PQueue * p;
	p = malloc(sizeof(PQueue));
	if (p == NULL) printf("\n***Failed Malloc Initialization***\n"); //unsuccessful malloc
	
	Node * q; //dummy
	q = malloc(sizeof(Node));
	if (q == NULL) printf("\n***Failed Malloc Initialization***\n"); //unsuccessful malloc
	q->item = 0; //a number not included in the range of numbers to be inserted into the list (1-10)
	q->priority = -1;
	
	Node * r; //dummy
	r = malloc(sizeof(Node));
	if (r == NULL) printf("\n***Failed Malloc Initialization***\n"); //unsuccessful malloc
	r->item = 0; //a number not included in the range of numbers to be inserted into the list (1-10)
	r->priority = -1;
	
	p->size = 0; 
	p->rear = q; 
	p->front = r;
	q->next = r;
	r->back = q;
	q->back = NULL;
	r->next = NULL;
	return (p);
}

/*insertPQ: O(n);
	This function inserts a new node into the queue with an integer item and float priority
	
	Return codes:
		0: successful insertion
		-1: failed malloc
*/
int insertPQ(int inp, float pri, PQueue * p)
{
	Node * newNode = malloc(sizeof(Node));
	if (newNode == NULL) return (-1); //unsuccessful malloc 
	p->size++; 
	newNode->item = inp; 
	newNode->priority = pri;
	
	Node * temp;
	temp = p->rear; //dummy
		
	while(temp->next->priority > pri) //since both dummies have items 
		{
			temp = temp->next; //moving temp to node previous to where newnode is inserted
		}
		
	newNode->next = temp->next; //if insertion at the end of the queue, temp-next is simply NULL
	newNode->back = temp;
	newNode->next->back = newNode;
	temp->next = newNode;
	return(0);
}

/*deleteMaxPQ: O(1); //THIS HAS TO BE O(1)
	This function deletes the node with the higest priority and returns it by reference to main

	Return codes:
		0: successful delete max
		-1: empty queue
*/
int deleteMaxPQ(PQueue * p, int * inp)
{
	Node * q = p->rear;
	if (q->next == p->front) return(-1); //empty queue
	else
	{
		p->size--;
		*inp = q->next->item;
		Node * temp = q->next;
		q->next = q->next->next; 
		temp->next->back = q;
		free(temp);
		return(0);
	}
}

/*deleteMinPQ: O(1); //THIS HAS TO BE O(1)
	This function deletes the node with the lowest priority and returns it by reference to main

	Return codes:
		0: successful delete max
		-1: empty queue
*/
int deleteMinPQ(PQueue * p, int * inp)
{
	Node * r = p->front;
	if (r->back == p->rear) return(-1); //empty queue
	else
	{
		p->size--;
		*inp = r->back->item;
		Node * temp = r->back;
		r->back = r->back->back; 
		temp->back->next = r;
		free(temp);
		return(0);
	}
}


/*getSizePQ: O(1); //THIS HAS TO BE O(1)
	This functions returns the current size of the queue
*/
int getSizePQ(PQueue * p)
{
	return(p->size);
}

/*reInitPQ: O(n);
	This function reinits an existing priority queue as an empty priority queue
*/
void reInitPQ(PQueue * p)
{
	Node* tempdummy = p->rear;
	Node* temp;
	p->rear = p->rear->next;
	while(p->rear != p->front) //if the node is non-null
	{
		temp = p->rear; 
		p->rear = p->rear->next;
		free(temp); //free the node previous stored in temp
	}
	p->size = 0;
	p->rear = tempdummy;
	tempdummy->next = p->front;
	p->front->back = tempdummy;
	printf("\nQueue has been reinitialized\n");
}

/*freePQ: O(n);
	This function frees all of the ememory allocated for the queue
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
	printf("\nQueue has been freed\n");
}

/*printPQ: O(n);
	This function prints the current Queue to the screen
*/
void printPQ(PQueue * p)
{
	Node * q = p->rear->next;
	if (q == p->front) printf("EMPTY QUEUE\n");
	else //non-empty queue
	{
		printf("Item Priority\n");
		while(q->next != p->front)
			{
				printf("%d    %.2f\n", q->item, q->priority);
				q = q->next;
			}
		printf("%d    %.2f\n", q->item, q->priority); //printing the last item in queue
	}
}

