#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void nth_power(int *arr, int n, int size) {
    int i;
    for(i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*arr_18(D) + _3' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        arr[i] = pow(arr[i], n);
    }
}

int main() {
    int* arr;
    int i, size, n;
    
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    arr = (int*) malloc(size * sizeof(int));
    if(arr == NULL) {
        printf("Memory not allocated.\n");
        return 1;
    }

    printf("Enter the elements in the array: ");
    for(i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the power: ");
    scanf("%d", &n);

    nth_power(arr, n, size);

    printf("Array after the operation: ");
    for(i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);

    return 0;
}