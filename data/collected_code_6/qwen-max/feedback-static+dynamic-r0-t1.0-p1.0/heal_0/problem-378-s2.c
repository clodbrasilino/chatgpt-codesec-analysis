#include <stdio.h>
#include <stdlib.h>

void shift_last_to_first(int *arr, int size) {
    if (size < 2) return;
    int last = arr[size - 1];
    for (int i = size - 1; i > 0; --i) {
        arr[i] = arr[i - 1];
    }
    arr[0] = last;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    shift_last_to_first(arr, size);
    
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}