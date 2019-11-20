#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int empID, age;
	float salary;
} Record;

int readRecordFile(char *filename, Record ***array);

int main(void){
	Record **array;
	char* filename = "employee.csv";
	
	int size = readRecordFile(filename, &array);
	printf("Size = %d", size);
	return 0;
}

int readRecordFile(char *filename, Record ***array){
	FILE *fp;
	fp = fopen(filename, "r");
	
	int size;
	if(fp){
		fscanf(fp, "%d\n", &size);
		
		*array = malloc(sizeof(Record*)*size);
		 
		 if(*array == NULL){
			 fclose(fp);
			 return(0);
		 }
		 
		 for (int i = 0; i < size; i++){
			 *array[i] = malloc(sizeof(Record));
			 
			 if(*array[i] == NULL){
				 fclose(fp);
				 
				 for (int j = 0; j < i; j++){
					 free(*array[j]);
					 *array[j] = NULL;
				 }
				 
				 free(*array);
				 *array = NULL;
				 return 0;
			 }
			 
			 fscanf(fp, "%d,%f,%d\n", &(((*array)[i])->empID), &(((*array)[i])->salary), &(((*array)[i])->age));
		 }
		 
		 fclose(fp);
		 return size;
		
	} else{
		return -1;
	}
}