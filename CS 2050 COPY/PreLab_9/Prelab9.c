//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Prelab 9, 10/5/19

//Implementation of a linked list using a single Dummy Node at the head and a List Node with 
	//a stored size, and head and tail Node pointers
//All of the required functions are time independent of the current length of the list

#include <stdio.h>
#include <stdlib.h>

typedef struct nodestruct {    
	int item;    
	struct nodestruct *next;
	} Node;
	
typedef struct liststruct {
	int size;
	Node * head, * tail;
	} List;
	
List *initIntegerList();
int insertAtHead(int, List*);
int insertAtTail(int, List*);
int removeHead(List*);
int getListSize(List*);
void printHead(List*);
void moveHeadToTail(List*);

void printList(List *); //this function IS dependent on the size of the List, but is not required
void freeList(List*); //this function IS dependent on the size of the List, but is not required
void errorchk (int);
int menu (void);
int inputfn(void);

/*main:
	See function descriptions below, main just iterates as necessary
*/
int main (void)
{
	List * head;
	head = initIntegerList(); //head = dummy node
	
	int sentinel = 0; //sentinel is the selection value from the menu function
	int input = 0; //the value the user wants to store in the new Node 
	int error = 0; //return values signal successful or unsuccessful completion (malloc error)
	
	while (sentinel != 8)
	{
		sentinel = menu(); //display menu and prompt for selection

		if (sentinel == 1) //insertAtHead
		{
			input = inputfn();
			error = insertAtHead(input, head);
			errorchk(error);
			printList(head);
		}
		
		if (sentinel == 2) //insertAtTail
		{
			input = inputfn();
			error = insertAtTail(input, head);
			errorchk(error);
			printList(head);
		}
		
		if (sentinel == 3) //removeHead
		{
			input = removeHead(head);
			puts("");
			printList(head);
			printf("Int stored in the removed node was %d\n", input);
		}
		
		if (sentinel == 4) //getListSize
		{
			input = getListSize(head);
			printf("\nNumber of elements in list = %d\n", input);
		}
		
		if (sentinel == 5) //printHead
		{
			printHead(head);
		}
		
		if (sentinel == 6) //moveHeadToTail
		{
			moveHeadToTail(head);
			puts("");
			printList(head);
		}
		
		if (sentinel == 7) //printList
		{
			puts("");
			printList(head);
		}
	}
	
	freeList(head);
	head = NULL;
	return (0);
}

/*initIntegerList:
	This function returns one dummy node with 0 stored in size, the dummy points to NULL
*/
List * initIntegerList()
{
	List * p; //the List node with pointers to the head and tail
	p = malloc(sizeof(List));
	if (p == NULL) printf("\n***Failed Malloc Initialization***\n");
	p->size = 0; 
 
	Node * q; //a single dummy node
	q = malloc(sizeof(Node));
	if (q == NULL) printf("\n***Failed Malloc Initialization***\n");
	
	q->next = NULL; 
	q->item = 999999999;
	p->head = q; //pointing both pointers in the List* to the dummy node
	p->tail = q;
	
	return (p);
}

/*insertAtHead: 	
	This function inserts a node at the head of the list by pointing the new node to the node just past
	the dummy, and pointing the dummy to the new node. 
	
	return value codes:
		-1 = failed malloc
		1 = successful insertion at head
*/
int insertAtHead(int inp, List* p)
{
	Node* newNode = malloc(sizeof(Node));
	if(newNode == NULL) return (-1); //if unsuccessful malloc 
	p->size++; //incrementing the size variable
	newNode->item = inp; 
	
	newNode->next =  p->head->next; //pointing the new node one past the dummy
	p->head->next = newNode; //pointing the dummy to the new head
	if (newNode->next == NULL) p->tail = newNode; //if first insertion, tail must be moved to newNode
	return(1);
}

/*insertAtTail:
	This function inserts a node at the tail of the list by pointing the new node to NULL, and
	pointing the tail pointer to the new node. 
	
	return value codes:
		-1 = failed malloc
		0 = successful insertion at tail
*/
int insertAtTail(int inp, List* p)
{
	Node* newNode = malloc(sizeof(Node));
	if(newNode == NULL) return (-1); //if unsuccessful malloc
	p->size++;
	newNode->item = inp; 
	
	newNode->next = NULL; //since no dummy at tail, set to Null
	p->tail->next = newNode; //pointing the old tail to the new node
	p->tail = newNode; //move the tail pointer to the new node
	return (0);
}

/*removeHead:
	THIS FUNCTION CAN NOT BE CALLED IF THERE ARE NO ENTRIES IN THE LIST
		- well techinically it can, but it returns 0; //THIS IS NOT REQUIRED BUT HELPED MY IMPLEMENTATION
	This function stores and returns the value in the node that is removed from the list.
	The function also temporarily stores the node to be removed so the head and tail(if necessary)
	can be rearranged
*/
int removeHead(List* p)
{
	if(p->head->next == NULL) //empty list
	{
		printf("\nEmpty List, nothing to remove");
		return(0);
	}
	Node* temp;
	int value = 0;
	p->size--; //decrementing the size variable
	value = p->head->next->item; //the value in the head about to be removed
	temp = p->head->next; //temp pointer to the node about to be removed 
	
	if(p->head->next->next == NULL) //if only one non-dummy in list, point tail to dummy and set dummy to NULL
	{
		p->tail = p->head; //point the tail back to the dummy
		p->head->next = NULL;  //point the dummy to NULL
		free(temp);
	}
	
	else //if 2 or more non-dummies in list
	{
		p->head->next = temp->next; //setting dummy to the node past temp
		free(temp);
	}
		
	return(value);
}

/*getListSize:
	This function returns the size of the list stored in the List*
*/
int getListSize(List* p)
{
	return (p->size);
}

/*printHead:	
	This function can be called by the user to print the integers in the node 
	at the head of the list
*/
void printHead(List *p)
{
	//if there is nothing except for the dummy
	if (p->head->next == NULL) printf("\nLinked List is empty\n");
	else printf("\nInt in head is: %d\n", (p->head->next->item));
}

/*moveHeadToTail:
	This function moves the head of the list to the tail
	If the list has 0 or 1 elements (non-distinct head and tail) print "error" message and exit
*/
void moveHeadToTail (List* p)
{
	// if 0 or 1 elements in List
	if (p->head->next == NULL || p->head->next->next == NULL) printf("\nNothing to switch");
	else
	{	
		Node* temp;
		temp = p->head->next; //temp is the head
		p->head->next = p->head->next->next; //pointing the dummy 1 past the head
		temp->next = NULL; //since it will be at the end of the list
		p->tail->next = temp; //pointing the current tail to the old head
		p->tail = temp; //pointing the tail to the old head
	}
}

/*printList:	
	This function can be called by the user to print the integers in the list
	This function also skips over the dummy nodes so they are not printed
	THIS FUNCTION IS NOT REQUIRED BUT IS TIME DEPENDENT ON THE SIZE OF THE LIST
*/
void printList(List *p)
{
	Node* temp;
	temp = p->head->next; //pointing temp past the dummy
	
	if (temp == NULL) printf("Nothing to print; Linked list is empty\n");
	else
	{
		while( temp != NULL) 
		{
			printf("%d ", temp->item);
			temp = temp->next;
		}
		puts("");
	}
}

/*freeList:
	This function frees all the memory allocated for the list by using a temp pointer to be 
	sure that no memory is accessed after it has been freed. The dummy node is freed within this function
	THIS FUNCTION IS NOT REQUIRED BUT IS TIME DEPENDENT ON THE SIZE OF THE LIST
*/
void freeList(List *p)
{
	Node* temp;
	while(p->head != NULL)
	{
		temp = p->head; //temp is the first node (including dummy) in the list
		p->head = p->head->next; //moving the head pointer to the next node
		free(temp);
	}

	free(p); //freeing the List struct
	printf("Linked list has been freed\n");
}	

/*errorchk:
	This function prints an error message if there is an unsuccessful malloc in 
	either insertAtTail and insertAtHead, and prints success messages for both as well
*/
void errorchk (int a)
{
	if (a == -1) printf("\n***Unsuccessful malloc of memory***\n");
	if (a == 0) printf("\nSuccessful Tail Insertion\n");
	if (a == 1) printf("\nSuccessful Head insertion\n");
}

/*menu:
	This function displays the menu options and prompts the user for selection
*/
int menu (void)
{
	int a = 0;
	printf("\nPress 1 to insert at head\n");
	printf("Press 2 to insert at tail\n");
	printf("Press 3 to remove the head\n");
	printf("Press 4 to get the current size of the list\n");
	printf("Press 5 to print the item in the current head of the list\n");
	printf("Press 6 to move the head to the tail\n");
	printf("Press 7 to print the whole list\n");
	printf("Press 8 to free the whole list\n");
	printf("Enter a selection: ");
	scanf("%d", &a);
	return (a);
}

/*inputfn:
	this function requests an integer from the user to be inserted into the list
*/
int inputfn(void)
{
	int a = 0;
	printf("Enter a value to insert into the list: ");
	scanf("%d", &a);
	return (a);
}