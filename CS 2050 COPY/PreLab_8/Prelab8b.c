//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Prelab 8, 10/5/19

//Linked List implementation with Dummy Nodes

#include <stdio.h>
#include <stdlib.h>

typedef struct liststruct{ //struct that holds an int and pointer
	int item;
	struct liststruct *next;
	}List;

List* initIntegerList();
int insertAtHead(int inp, List* p);
int insertAtTail(int inp, List* p);
void printList(List *q);
void freeList(List *q);

int menu(void);
int inputfn(void);
void errorchk (int a);

int main (void)
{
	List * head;
	head = initIntegerList(); //head = dummy nodes

	int sentinel = 0; //sentinel is the selection value from the menu function
	int input = 0; //the value the user wants to store in the new Node
	int error = 0; //return values signal successful or unsuccessful completion (malloc error)
	while (sentinel != 4)
	{
		sentinel = menu(); //display menu and prompt for selection

		if (sentinel == 1) //insertAtHead
		{
			input = inputfn();
			error = insertAtHead(input, head);
			errorchk(error);
		}
		
		if (sentinel == 2) //insertAtTail
		{
			input = inputfn();
			error = insertAtTail(input, head);
			errorchk(error);
		}
		
		if (sentinel == 3) //printList
		{
			printList(head);
		}
	}
	freeList(head);
	return (0);
}

/*initIntegerList:
	This function returns two dummy nodes with 8888 and 9999 stored in them respectively
*/
List * initIntegerList()
{
	List * p;
	p = malloc(sizeof(List));
	p->item = 8888;
	p->next = malloc(sizeof(List));
	p->next->item = 9999;
	p->next->next = NULL;
	return (p);
}

/*menu:
	This function displays the menu options and prompts the user for selection
*/
int menu (void)
{
	int a = 0;
	printf("\nPress 1 to insert at head\n");
	printf("Press 2 to insert at tail\n");
	printf("Press 3 to print the current list\n");
	printf("Press 4 to free the list and terminate the program\n");
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

/*errorchk:
	This function prints an error message if there is an unsuccessful malloc in 
	either insertAtTail and insertAtHead, and prints success messages for both as well
*/
void errorchk (int a)
{
	if (a == -1) printf("\n***Unsuccessful malloc of memory***\n");
	if (a == 0) printf("\nSuccessful insertion at head!!!\n");
	if (a == 1) printf("\nSuccessful insertion at tail!!!\n");
}

/*insertAtHead: 	
	This function inserts an int at the head of the list
	
	return value codes:
		-1 = failed malloc
		0 = successful insertion at head
*/
int insertAtHead(int inp, List* p)
{
	List* newList = malloc(sizeof(List));
	if(newList == NULL) //if unsuccessful malloc
	{
		return (-1); //error code
	}
	
	newList->item = inp; //store the passed input in the item of the struct
	newList->next =  p->next; //pointing the new node 1 past the dummy node
	p->next = newList; //pointing the dummy node to the new node
	return(0);
}

/*insertAtTail:		//same procedure as insertAtHead
	This function inserts an int at the tail of a list

	return value codes:
		-1 = failed malloc
		1 = successful insertion at tail
*/
int insertAtTail(int inp, List* p)
{
	List* newList = malloc(sizeof(List));
	if(newList == NULL) //if unsuccessful malloc
	{
		return (-1); //error code
	}
	
	newList->item = inp;
	
	while (p->next->next != NULL)
	{ 											                                                 	
		p = p->next;
	}
	
	newList->next =  p->next; //pointing the new node to the dummy node
	p->next = newList; //pointing the list to the new node
	
	return(1);
}

/*printList:	
	This function can be called by the user to print the integers in the list
	This function also skips over the dummy nodes so they are not printed
*/
void printList(List *q)
{
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
		//you may consider implementing so that the users pointer is set 
			//to NULL in the process (prevent user from accidentally
			//referencing freed memory)
*/
void freeList(List *q)
{
	List* temp;
	while(q != NULL) //if the node is non-null
	{
		temp = q; 
		q = q->next; //move the pointer to the next node
		free(temp); //free the node previous stored in temp
	}
}	