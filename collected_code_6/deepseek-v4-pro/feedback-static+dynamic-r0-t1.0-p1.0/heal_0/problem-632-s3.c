#include <stdio.h>
#include <stdlib.h>

void move_zeroes_to_end(int *arr, int size) {
    int non_zero_index = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] != 0) {
            arr[non_zero_index++] = arr[i];
        }
    }
    
    while (non_zero_index < size) {
        arr[non_zero_index++] = 0;
    }
}

int main(void) {
    int arr[] = {0, 1, 0, 3, 12, 0, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    move_zeroes_to_end(arr, size);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}