//Using breakpoint

#include <stdio.h>
#include <stdlib.h>

int main (void)
{	
	int array[3] = {0,1,2};
	int *ptr = NULL;
	
	//ptr = malloc(sizeof(int)); //insert a breakpoint so the code stops and you can see where the issue is 
								 //simply click to add a breakpoint on the very left column in VS, the program will stop there
	int n = 5;
	*ptr = array[0];
	
	printf("Current n is %d, current value in Ptr is %d\n", n, *ptr);
	
	return(0);
}

//if you set a BP in main, you will not have any access to variables in any calling functions