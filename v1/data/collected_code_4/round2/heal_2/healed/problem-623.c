#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void nth_power(int *arr, int n, int size) {
    int i;
    for(i = 0; i < size; i++) {
        arr[i] = (int)pow((double)arr[i], n);
    }
}

int main() {
    int size, n;
    
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int* arr = (int*) calloc(size, sizeof(int));
    if(arr == NULL) {
        printf("Memory not allocated.\n");
        return 1;
    }

    printf("Enter the elements in the array: ");
    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the power: ");
    scanf("%d", &n);

    nth_power(arr, n, size);

    printf("Array after the operation: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);

    return 0;
}