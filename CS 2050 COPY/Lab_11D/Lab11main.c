int main (void)
{
	srand(time(NULL));
	PQueue * pq;
	pq = initPQ(); 
	
	printPQ(pq); //empty queue operations
	reInitPQ(pq);
	
	int input = 0;
	float rank = 0;
	int error = 0;
	
	for (int i = 0; i<4; i++) //4 enqueue
	{
		input = ((rand()%9)+1);
		rank = (float)rand()/(float)(RAND_MAX/1);
		error = insertPQ(input, rank, pq);
		if (error == -1) break;
		printPQ(pq);
	}
	
	for(int i=0; i<6; i++) //6 dequeue
	{
		error = deleteMinPQ(pq, &input);
		if(error == -1) printf("*****Empty Queue; Nothing to Dequeue*****\n");
		else
		{
			printf("\n\nKey removed from Queue was %d", input);
			printPQ(pq);
		}
	}
	
	for (int i = 0; i<4; i++) //4 enqueue
	{
		input = ((rand()%9)+1);
		rank = (float)rand()/(float)(RAND_MAX/1);
		error = insertPQ(input, rank, pq);
		if (error == -1) break;
		printPQ(pq);
	}
	
	reInitPQ(pq);
	
	for (int i = 0; i<4; i++) //4 enqueue
	{
		input = ((rand()%9)+1);
		rank = (float)rand()/(float)(RAND_MAX/1);
		error = insertPQ(input, rank, pq);
		if (error == -1) break;
		printPQ(pq);
	}
	
	freePQ(pq);
	pq = NULL;
	return(0);
}