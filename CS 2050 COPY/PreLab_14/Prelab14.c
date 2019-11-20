//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Prelab 14, 11/15/19

//Binary Trees
//create trees with a known amount of nodes and height to test the functions

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodestruct {    
	int key;
	struct nodestruct *left, *right;
	} Tree;

Tree * randInsert (int, Tree *); 
int getHeight (Tree *); 
int countNodes (Tree *); 

int main (void)
{
	srand(time(NULL));
	Tree * oaktree = NULL;
	for (int i = 0; i < 1000000; i++) oaktree = randInsert((rand()%10), oaktree);
	printf("\nHeight of the tree is %d nodes", getHeight(oaktree));
	printf("\nSize of the tree is %d nodes\n", countNodes(oaktree));
	return(0);
}

/*insertBT:
	Inserts each data into a binary tree (NOT a BST) by using a random integer to 
	determine whether to insert left or right and recursively calling until a NULL node
	is reached. The passed data is stored in the new node.
*/
Tree * randInsert (int data, Tree * t)
{
	if (t == NULL) //if we have reached a non-empty node
	{
		t = malloc(sizeof(Tree));
		if (t == NULL) printf("\n\n*****Failed Malloc*****\n\n");
		t->key = data;
		t->left = NULL;
		t->right = NULL;
		return(t); //returning the new node (for recursion)
	}
	
	if ((rand()%2) == 1) t->left = randInsert(data, t->left); //randomly deciding to go left or right and recursively calling the function
	else t->right = randInsert(data, t->right);
	return (t); //returning the new binary tree back to main
}

/*getHeight:
Determines the maximum height of a given binary tree recursively and returns the height to main
	expected height of the tree is O(log(N))
*/
int getHeight (Tree * t)
{
	if (t == NULL) return 0; 
    else 
    { 
       int lHeight = getHeight(t->left); //recursively finding the heights of the subtrees
       int rHeight = getHeight(t->right); 
       if (lHeight > rHeight) return(lHeight + 1); //returning the larger height to main (+1 includes the 'head' node)
       else return(rHeight + 1); 
    }  
}

/*countNodes:
	determines the number of nodes in a given binary tree recursively and returns the size to main
*/
int countNodes (Tree * t)
{
	if (t == NULL) return 0; 
    else return(countNodes(t->left) + 1 + countNodes(t->right));   
}