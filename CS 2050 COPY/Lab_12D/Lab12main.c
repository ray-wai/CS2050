int main (void)
{
	srand(time(NULL));
	PQueue * pq;
	pq = initPQ(25); //initializing an array with 25 ints
	int deput = 0;
	int error = 0;
	
	//*********************NOTE: EMPTY QUEUE OPERATION OF DELETEMAX AND FINDIDX ARE TESTED AND WORK CORRECTLY**********
	
	for (int i = 0; i < 33; i++) 
	{
		int find = ((rand()%100)+1); //random int
		error = insertPQ(pq, find); 
		if (error == -1) printf("*****UNSUCCESSFUL INSERTION*****\n");
		printPQ(pq);
		if (i%5 == 4)
		{
			error = DeQueue(pq, &deput); 
			if (error == -1) printf("\n\n*****UNSUCCESSFUL DELETION; EMPTY LIST*****\n\n");
			else printf("SUCCESSFUL DELETION, INT REMOVED WAS %d\n", deput);
			
			error = findIdx(pq, find);
			if (error == -1) printf("%d was not found in the PQ\n", find);
			else printf("%d was found in the PQ at index %d\n", find, error);
		}
	}
	freePQ(pq);
	pq = NULL;
	return(0);
}