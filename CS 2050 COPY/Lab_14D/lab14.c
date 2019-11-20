#include "lab14.h"

/*insertBT:
	Inserts each key into a binary tree (NOT a BST) by using a random integer to 
	determine whether to insert left or right and recursively calling until a NULL node
	is reached. The passed data is stored in the new node. 
*/
treeNode * insertBT (treeNode * t, int key)
{
	if (t == NULL) //if we have reached a non-empty node
	{
		t = malloc(sizeof(treeNode));
		if (t == NULL) printf("\n\n*****Failed Malloc*****\n\n");
		t->data = key;
		t->left = NULL;
		t->right = NULL;
		return(t); //returning the new node (for recursion)
	}
	
	if ((rand()%2) == 1) t->left = insertBT(t->left, key); //randomly deciding to go left or right and recursively calling the function
	else t->right = insertBT(t->right, key);
	return (t); //returning the new binary tree back to main
}

/*printBT:
	This function receives the current binary tree and prints out all the values in the tree recursively
*/
void printBT (treeNode * t)
{
	if (t == NULL) printf("Binary Tree is empty!!!");
	else //non-empty BT
	{
		printf("%d ", t->data); 
		if (t->left != NULL) printBT(t->left); 
		if (t->right != NULL) printBT(t->right);
	}
}

/*freeTree:
	This function recursively traverses down the tree and frees each node making sure that memory is not accessed after it has been freed
*/
void freeTree(treeNode* t)
{
	if (t == NULL) printf("\nBinary Tree is Empty; Nothing to Free\n");
	else //non-empty BT
	{
		if (t->left != NULL) freeTree(t->left);
		if (t->right != NULL) freeTree(t->right);
		free(t);
	}
}

/*countEvenKey:
	This function recursively counts the number of even keys in the tree and returns that value to main by reference
	It is assumed that the integer stored in passed int* has already been initialized to 0 in main
*/
void countEvenKey(treeNode* t, int* a)
{
	if (t == NULL) *a = 0; //empty binary tree
	else
	{
		if (t->data % 2 == 0) *a += 1; //if the node is even, add 1 to the running total of even keys
		if (t->left != NULL) countEvenKey(t->left, a); 
		if (t->right != NULL) countEvenKey(t->right, a);
	}
}
