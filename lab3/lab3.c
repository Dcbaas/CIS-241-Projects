#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main ()
{
	const int MaxSize = 75000;
	int i, j, temp;

	printf ("\nStart to Measure Time\n");

	clock_t begin = clock();

	int staticArray[MaxSize];

	for (i=0; i<MaxSize; i++)
		staticArray[i] = MaxSize-i;

	for (i=0; i<MaxSize-1; i++)
		for (j=MaxSize-1; j>i; j--)
			if (staticArray[j-1] > staticArray[j])
			{
				temp = staticArray[j-1];
				staticArray[j-1] = staticArray[j];
				staticArray[j] = temp;
			}

	clock_t middle = clock();


	// write code below to perform bubble sort on a dynamically allocation array

    printf("\nStart the Dynamic Array Sorting\n");
    //Create the array and populate 
    int* dynamic_array = (int*) calloc(MaxSize, sizeof(int));

    if(dynamic_array == NULL){
        fprintf(stderr, "ERROR WITH MEMORY ALLOCATION");
        //In errno.h 12 is macroed to out of memory
        return 12;
    }
    //In CIS 350, we were told to never call variables single characters.
    int* address;
    int* address2;

    for (address = dynamic_array, i = MaxSize; 
        address < dynamic_array + (MaxSize - 1); ++address, --i){
        *address = i;
    }
    
    for(address = dynamic_array; address < dynamic_array + (MaxSize -1); ++address){
        for(address2 = dynamic_array + (MaxSize - 1); address2 > address; --address2){
            if(*(address2-1) > *address2){
                temp = *(address2 - 1);
                *(address2 -1) = *address2;
                *address2 = temp;
            }
        }
    }

    clock_t end = clock();

    printf("Time Used with Array Indexes: \t %lf%s\n",
    (double) (middle - begin)/CLOCKS_PER_SEC, " Second");
    printf("Time Used with Pointers: \t %lf%s\n\n", 
    (double) (end - middle)/CLOCKS_PER_SEC, " Second");

    free(dynamic_array);
	return 0;
}
