#include "lab14.h"

int main (void)
{
	srand(time(NULL));
	treeNode * oaktree = NULL;
	
	printf("\nCurrent BT is: "); //empty BT operations
	printBT(oaktree);
	int odd = 0;
	countEvenKey(oaktree, &odd);
	printf("\nNumber of even nodes is %d", odd);
	freeTree(oaktree);
			
	for (int i = 0; i < 10; i++)
	{
		oaktree = insertBT(oaktree, (rand()%10));
	
		printf("\nCurrent BT is: ");
		printBT(oaktree);
		
		int even = 0;
		countEvenKey(oaktree, &even);
		printf("\nNumber of even nodes is %d", even);
	}
	
	freeTree(oaktree);
	printf("\nTree Has Been Freed!!!");
	return(0);
}