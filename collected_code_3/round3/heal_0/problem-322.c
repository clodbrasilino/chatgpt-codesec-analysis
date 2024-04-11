#include <stdio.h>
#include <stdlib.h>

void find_min_indices(int* arr, int size) {
    int min = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    for(int i = 0; i < size; i++) {
        if(arr[i] == min) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {4, 2, 9, 2, 0, 1, 0, 5, 0, 3, 2, 0, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    find_min_indices(arr, size);
    return 0;
}