//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 8, 10/8/19

//Implementation of a linked list using Dummy Nodes, insert at head and insert ascending

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodestruct {    
	int item;    
	struct nodestruct *next;
	} Node;
	
Node *initIntegerList();
int insertAscend(Node*,int);
int insertAtHead(Node*,int);
void printList(Node*);
void freeList(Node*);
int computeSum(Node*);
void errorchk (int);

/*main:
	Initialize a linked list with head and tail dummy nodes
	Insert in ascending order 5 times and print the list and sum each time
	Insert at head 5 times and print the list and sum each time
	Free the List
*/
int main (void)
{
	srand(time(NULL)); //for random integer generator
	Node * head;
	head = initIntegerList(); //head = dummy nodes

	int input = 0; //the value the user wants to store in the new Node (randomly generated)
	int error = 0; //return values signal successful or unsuccessful completion (malloc error)
	
	printList(head); //empty list operations
	printf("Sum is %d\n", computeSum(head));
	
	for (int i = 0; i < 5; i++) //5 ascending insertions
	{
		input = ((rand()%10)+1);
		error = insertAscend(head, input);
		errorchk(error);
		printList(head);
		printf("\nSum is %d\n", computeSum(head));
	}
	
	for (int i = 0; i < 5; i++) //5 head insertions
	{
		input = ((rand()%10)+1);
		error = insertAtHead(head, input);
		errorchk(error);
		printList(head);
		printf("\nSum is %d\n", computeSum(head));
	}
	
	freeList(head);
	head = NULL;
	return (0);
}

/*initIntegerList:
	This function returns two dummy nodes with 100 stored in them, the last dummy points to NULL
*/
Node * initIntegerList()
{
	Node * p;
	p = malloc(sizeof(Node));
	p->item = 100; 
	p->next = malloc(sizeof(Node));
	p->next->item = 100; 
	p->next->next = NULL;
	return (p);
}

/*insertAscend:
	This function inserts a new node into the list in ascending order.
	
	The while loop moves the pointer to the node just before the node with item value
	equal or greater than the new node item. This allows us to point the new node to the node
	with item value equal or greater than, and point the node with value less than the new item node to 
	the new node. 
	
	For example, assume a list with 3 5; to insert 4, point 4 to 5, and point 3 to 4
	
	It is also worth noting that since dummies are initialized to 100, the while loop does nothing 
	the very first time this function is called since we are inputting values between 1-10
	
	return value codes:
		0: successful insertion
		-1: unsuccessful insertion (failed malloc)
*/
int insertAscend(Node* p,int inp)
{
	Node* newList = malloc(sizeof(Node));
	if(newList == NULL) // unsuccessful malloc
	{
		return (-1); 
	}
	newList->item = inp; 
	while (p->next->item < inp) p = p->next; 
	newList->next = p->next; //point newList to the node = or greater than it's value
	p->next = newList; //point the previous node to newList
	return(0);
}

/*insertAtHead: 	
	This function inserts an int at the head of the list by pointing the new node to the node just past the 
	head dummy, and pointing the head dummy to the new node. 
	
	return value codes:
		-1 = failed malloc
		1 = successful insertion at head
*/
int insertAtHead(Node* p, int inp)
{
	Node* newList = malloc(sizeof(Node));
	if(newList == NULL) //if unsuccessful malloc
	{
		return (-1); 
	}
	newList->item = inp; 
	newList->next =  p->next; 
	p->next = newList; 
	return(1);
}

/*printList:	
	This function can be called by the user to print the integers in the list
	This function also skips over the dummy nodes so they are not printed
*/
void printList(Node *q)
{
	if (q->next->next == NULL) //if there is nothing except for dummy nodes
	{
		printf("\nLinked List is empty\n");
	}
	
	q = q->next; //skipping the first dummy node
	while( q->next != NULL) //ensuring we don't print the last dummy node
	{
		printf("%d ", q->item);
		q = q->next;
	}
}

/*freeList:
	This function frees all the memory allocated for the list by using a temp pointer to be 
	sure that no memory is accessed after it has been freed. The dummy nodes are freed within this function
*/
void freeList(Node *q)
{
	Node* temp;
	while(q != NULL) //if the node is non-null
	{
		temp = q; 
		q = q->next; //move the pointer to the next node
		free(temp); //free the node previous stored in temp
	}
	printf("Linked list has been freed\n");
}	

/*computeSum:
	This function sums all of the items in the linked list, skipping over the dummy nodes
	The function returns the sum to main
*/
int computeSum(Node* q)
{
	int sum = 0;
	q = q->next; //skipping the first dummy node
	while( q->next != NULL) //ensuring we don't sum the last dummy node
	{
		sum = sum + q->item;
		q = q->next;
	}
	return(sum);
}

/*errorchk:
	This function prints an error message if there is an unsuccessful malloc in 
	either insertAscend and insertAtHead, and prints success messages for both as well
*/
void errorchk (int a)
{
	if (a == -1) printf("\n***Unsuccessful malloc of memory***\n");
	if (a == 0) printf("Ascending insertion: Linked list is: ");
	if (a == 1) printf("Head insertion: Linked list is: ");
}