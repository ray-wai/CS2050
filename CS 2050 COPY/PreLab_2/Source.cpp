//Raymond Waidmann
//18157816, rcw5k2
//CS2050 Prelab 2

//creating a function to determine the number of number bigger and smaller than a given number in an array

#include <stdio.h>
#define SIZE 10 //size of the array
void getminmax(float array[], int size, int comparison, int* max, int* min);

int main(void)
{
	int m = 0; //number of values less than comparison
	int M = 0; //number of values greater than comparison
	int comparison = 2; //value to be compared to the numbers in the array
	float arr[SIZE] = {1.345, 234, 0, -12.333, 987, -1, 5.55, 6.345, -2.56, 4}; //a random array of size SIZE

	getminmax(arr, SIZE, comparison, &M, &m); //calling the function to get compare the values in the array to the comparison value
											  //pass the address of M and m so we can dereference them in the function and change them without having a return value

	printf("\nThe number of array entries bigger than %d is %d, the number smaller is %d\n", comparison, M, m); //displaying the results

}

void getminmax(float ARR[], int SZ, int CMP, int* BIG, int* SMALL)
{
	for (int i = 0; i < SZ; i++) //looping through the array
	{
		//printf("arr[%d] = %f\n", i, ARR[i]);
		if (ARR[i] > CMP)
			(*BIG)++; //if the value at the index in the array is bigger, dereference the address and add 1 to the value
		if (ARR[i] < CMP)
			(*SMALL)++; //if the value at the index in the array is smaller, dereference the address and add 1 to the value
	}
}