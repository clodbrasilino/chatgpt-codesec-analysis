#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void removeDuplicates(int* arr, int* size) {
    int i, j, k;
   
    for (i = 0; i < *size; i++) {
        for (j = i + 1; j < *size;) {
            if (arr[i] == arr[j]) {
                for (k = j; k < *size; k++) {
                    arr[k] = arr[k + 1];
                }
                (*size)--;
            } else {
                j++;
            }
        }
    }
}

int main() {
    int size = MAX_SIZE;
    int i;
    int* arr = (int*)malloc(sizeof(int)*size);
    
    if(arr == NULL) {
		printf("Error! memory not allocated.");
        exit(0);
	}
    
    printf("Enter %d elements for the tuple\n", size);
    
    for(i = 0; i < size; i++)
    {
       scanf("%d", arr + i);
    }
    
    removeDuplicates(arr, &size);
    
    printf("Tuple after removing duplicates is :\n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    
    free(arr);
    
    return 0;
}