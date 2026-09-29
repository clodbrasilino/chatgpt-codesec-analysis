#include <stdio.h>
#include <stdlib.h>

int remove_negatives(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0) {
            arr[new_size] = arr[i];
            new_size++;
        }
    }
    return new_size;
}

int main(void) {
    int arr[] = {1, -1, 2, -2, 3, -3, 0, -4};
    int new_size = remove_negatives(arr, sizeof(arr) / sizeof(arr[0]));
    
    for (int i = 0; i < new_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}