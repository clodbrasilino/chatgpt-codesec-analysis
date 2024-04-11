#include <stdio.h>
#include <stdlib.h>

void find_max_indexes(int* arr, int size) {
    int max = arr[0];
    int i;
    for(i = 1; i < size; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    for(i = 0; i < size; i++) {
        if(arr[i] == max) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 3, 5, 7, 7, 7, 2, 3, 7, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    find_max_indexes(arr, size);
    return 0;
}