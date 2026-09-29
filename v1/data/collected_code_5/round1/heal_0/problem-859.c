#include <stdio.h>
#include <stdlib.h>

void printSubLists(int *arr, int n) {
    for (int i = 0; i < (1<<n); i++) {
        printf("{ ");
        for (int j = 0; j < n; j++)
            if (i & (1<<j)) 
                printf("%d ", arr[j]);
        printf("}\n");
    }
}

int main() {
    int *arr;
    int n;

    printf("Enter number of elements in the array: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Size of array should be greater than zero\n");
        return -1;
    }

    arr = (int*)malloc(n * sizeof(int));

    if(arr == NULL) {
        printf("Failed to allocate memory!\n");
        return -1;
    }

    printf("Enter elements of the array: ");
    for(int i = 0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    printSubLists(arr, n);

    free(arr);
    
    return 0;
}