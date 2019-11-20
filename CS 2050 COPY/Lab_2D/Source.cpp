//Raymond Waidmann
//18157816, rcw5k2
//Lab 2, 8/27/19

//This program initializes an array and calls a function to find its sum and average and returns the values via pointers. The results are printed to the screen.

# include <stdlib.h>
# include <stdio.h>

void computeSumAve(int arr[], int size, int* sumPrt, float* avePtr); // function prototype

int main(void) 
{    
	int size = 10;    
	int sum;
	float average;
	int array[10] = {5,-9,8,2,-7,10,12,-9,3,-6};    
	
	computeSumAve(array, size, &sum, &average); //calling the function, passing the array and its size along with addresses to sum and average
												//note the addresses of sum and average are used so that we can pass them by reference
	printf("Array is ");
	for (int i = 0; i < size; i++) printf("%d, ", array[i]); //looping through the array and printing off the value at each index
	printf("\nSum of the array is: %d, average of array is: %.2f\n", sum, average); //displaying the results from the function call and rounding the average to 2 decimals
	return 0;
}

void computeSumAve(int ARRAY[], int SIZE, int* SUMPRT, float* AVEPTR) //this function finds the sum and average of an array of known size and returns the results to main by reference
{
	int RUNNINGSUM = 0; //creating a variable to keep 'tally' of the sum as we run through the array in the for loop
	for (int j = 0; j < SIZE; j++) RUNNINGSUM += ARRAY[j]; //looping through the array and summing all the values together
	(*SUMPRT) = RUNNINGSUM; //*SUMPRT is the same as "sum" in main, thus we are setting sum = RUNNINGSUM; the sum we found in this function call
	(*AVEPTR) = (((float)RUNNINGSUM) / SIZE); //*AVEPTR is the same as "average" in main, thus we are setting average = sum/size. 
										      //Note the cast of RUNNINGSUM to a float, this allows us to return a float back to main; not an integer value
}