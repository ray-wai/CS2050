//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 9, 10/5/19

//Implementation of a linked list using a List Node with a stored size, and head and tail Node pointers
//no dummy nodes should be used in this lab assignment

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodestruct {    
	int item;    
	struct nodestruct *next;
	} Node;

typedef struct {
    int size;
    Node *head, *tail;
	} List;

List *initIntegerList();
int insertAtHead(int, List*);
int removeTail(List*);
void emptyList(List*);
void freeList(List**);
void printList(List*);
void errorchk (int);

/*main:
	See function descriptions below, main just loops as described in the lab description
*/
int main (void)
{
	srand(time(NULL)); // for random integer generator  
	List * head;
	head = initIntegerList(); 
	printList(head); //empty list operation
	
	int input = 0; //the value the user wants to store in the new Node 
	int error = 0; //return values signal successful or unsuccessful completion (malloc error)
	
	for (int i = 0; i < 5; i++) //5 head insertions
	{
		input = ((rand()%10)+1);
		error = insertAtHead(input, head);
		errorchk(error);
		printList(head);
	}
	
	for (int i = 0; i < 2; i++) //2 tail deletions
	{
		input = removeTail(head);
		errorchk(input);
		printList(head);
	}
	
	emptyList(head); //emptying the list
	
	input = ((rand()%10)+1); //one more head insertion
	error = insertAtHead(input, head);
	errorchk(error);
	printList(head);
	
	freeList(&head); //freeing the whole list
	return (0);
}

/*initIntegerList; O(1) complexity:
	This function returns an empty list, both head and tail pointers point to NULL
*/
List * initIntegerList()
{
	List * p; 
	p = malloc(sizeof(List));
	if (p == NULL) printf("\n***Failed Malloc Initialization***\n"); //unsuccessful malloc
	p->size = 0; 
	p->head = NULL; //pointing both pointers in the List* to NULL
	p->tail = NULL;
	return (p);
}

/*insertAtHead; O(1) complexity:
	This function inserts a node at the head of the list by pointing the new node to the node currently
	at the head and moving the head pointer. 
	If the list is empty when this function is called, simply insert the Node and point both head and tail 
	pointers to the inserted node.
	
	return value codes:
		-1 = failed malloc
		-2 = successful insertion at head
*/
int insertAtHead(int inp, List* p)
{
	Node* newNode = malloc(sizeof(Node));
	if(newNode == NULL) return (-1); //unsuccessful malloc 
	p->size++; //incrementing the size variable since we are inserting a node
	newNode->item = inp; 
	
	if(p->head == NULL) //if the first insertion:
	{
		p->head = newNode;
		p->tail = newNode;
		newNode->next = NULL;
		return(-2);
	}
	
	else //if more than one node already in the list:
	{
		newNode->next = p->head;
		p->head = newNode;
		return(-2);
	}
}

/*removeTail; O(n) complexity:
	This function removes the node at the tail and returns it's key
	If this function is called on an empty list, an error message is displayed and 0 is returned to main
	If this function is called on a list with 1 node, free the node and point the head and tail pointers to NULL
	If this function is called on a list with greater than 1 node, use a temp pointer to find the node previous 
	to the current tail, free the tail, and point the tail pointer the temp node. 
	
	return values:
		0 = empty list, nothing to remove
		integer > 0 = key in removed node
*/
int removeTail(List* p)
{
	if (p->head == NULL) return(0); //empty list
	else
	{
		p->size--;
		int value = 0;
		value = p->tail->item; //value of node about to be removed
		
		if(p->head->next == NULL) //only 1 item in list, free the node and set pointers to NULL
		{
			free(p->head); 
			p->head = NULL;
			p->tail = NULL;
		}
		
		else //2 or more items in list
		{
			Node* temp; //temp pointer to the node 1 previous to the node about to be removed
			temp = p->head;
			while(temp->next->next != NULL) temp = temp->next; 
			free(p->tail); 
			p->tail = temp; //pointing the tail pointer to the node previous to it
			p->tail->next = NULL; //pointing the last node to NULL
		}
		return(value);
	}
}

/*emptyList; O(n) complexity:
	This function removes and frees all the nodes in the linked list and sets the head and tail pointers to 0
	For an already empty list, display an error message and exit
*/
void emptyList(List* p)
{
	if (p->head == NULL) printf("Nothing in the List; nothing to empty\n"); //empty list
	else //non-empty list
	{
		while(p->head != NULL)
		{
			Node* temp;
			temp = p->head;
			p->head = p->head->next;
			free(temp);
		}
		p->tail = NULL;
		p->size = 0;
		printf("List has been emptied\n");
	}
}

/*freeList; O(n) complexity:
	This function frees all the memory allocated for the list by using a temp pointer to be 
	sure that no memory is accessed after it has been freed. 
*/
void freeList(List** p)
{
	Node* temp;
	while((*p)->head != NULL)
	{
		temp = (*p)->head;
		(*p)->head = (*p)->head->next;
		free(temp);
	}
	free(*p);
	*p = NULL;
	printf("Linked list has been freed\n");
}

/*printList; O(n) complexity:
	This function can be called by the user to print the integers in the list
*/
void printList(List *p)
{
	Node* temp;
	temp = p->head; //pointing temp to the first node
	
	if (temp == NULL) printf("\nLinked list is empty; Nothing to print\n");
	else
	{
		while(temp != NULL) 
		{
			printf("%d ", temp->item);
			temp = temp->next;
		}
		puts("");
	}
}

/*errorchk:
	This function prints an error message if there is an unsuccessful malloc in 
	either insertAtTail and insertAtHead, and prints success messages for both as well
*/
void errorchk (int a)
{
	if (a == -1) printf("\n***Unsuccessful malloc of memory***\n");
	if (a == -2) printf("Head insertion; List is: ");
	if (a == 0) printf("\nEmpty List, nothing to remove");
	if (a > 0) printf("Tail deletion; List is: ");
}
