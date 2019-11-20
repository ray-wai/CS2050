//Raymond Waidmann
//18157816, rcw5k2
//CS2050, Lab 14, 11/19/19

//This program allows for creation of a binary tree with random insertion, rints the BT, counts the number of 
//even nodes in the BT, and frees the BT. Recursion is heavily utilized throughout. 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {    
	int data;
	struct node *left, *right;
	} treeNode;

treeNode * insertBT (treeNode*, int); 
void printBT (treeNode*);
void freeTree(treeNode*);
void countEvenKey(treeNode*, int*);