# include <stdlib.h>
# include <stdio.h>

int identifyEvenNum(int arr[], int size); // function prototype

int main(void)
{
	int size = 7;
	int array[7] = { 7,18,9,20,16,5,8 };
	int evens; //creating an integer to hold the return value from the identifyEvenNum call function
	evens = identifyEvenNum(array, size); //setting evens to the return value of the call function

	printf("Array is: ");
	for (int j = 0; j < size; j++) //iterating through the array
	{
		printf("%d, ", array[j]); //printing off each value in the array
	}
	puts("");
	printf("Number of even integers is %d\n\n", evens); //printing out how many evens there are
	return 0;
}

int identifyEvenNum(int a[], int size)
{
	int count = 0; //setting a counting variable to count the number of evens
	for (int i = 0; i < size; i++) //iterating through the array
	{
		if (a[i] % 2 == 0) //if the number in the array is divisible by 2 with a remainder of 0...
		{
			count++; //add one to count
		}
	}
	return (count); //return count to main once all the numbers in the array have been checked
}
