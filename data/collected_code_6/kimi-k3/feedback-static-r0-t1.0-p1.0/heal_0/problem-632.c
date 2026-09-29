#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void move_zeroes(int *arr, size_t size) {
    if (arr == NULL) {
        return;
    }
    
    size_t write_pos = 0;
    
    for (size_t i = 0; i < size; i++) {
        if (arr[i] != 0) {
            arr[write_pos] = arr[i];
            write_pos++;
        }
    }
    
    for (size_t i = write_pos; i < size; i++) {
        arr[i] = 0;
    }
}

int main(void) {
    int arr[] = {0, 1, 0, 3, 12, 0, 5, 0, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    move_zeroes(arr, size);
    
    printf("Modified array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}