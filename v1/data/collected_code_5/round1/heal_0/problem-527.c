#include <stdio.h>
#define MAX_SIZE 100

void printPairs(int array[], int array_size, int sum)
{
    int i, j;
	
    for (i = 0; i < array_size - 1; i++) 
    {     
        for (j = i+1; j < array_size; j++) 
        {       
            if(array[i] + array[j] == sum)            
            {
                printf("Pairs with sum %d are (%d, %d)\n", sum, array[i], array[j]);
            }
        }
    }
}

int main()
{
    int array[MAX_SIZE], i, n, sum;
   
    printf("Enter size of the array : ");
    scanf("%d", &n);
 
    printf("Enter elements in array : ");
    for(i=0; i<n; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Enter the sum : ");
    scanf("%d", &sum);

    if (n > 2)
    {
        printPairs(array, n, sum);
    }
    else
    {
        printf("\nInsufficient elements in array.");
    }

    return 0;
}