#include <stdio.h>
#include <stdlib.h>

void find_min_indices(int* arr, int len) {
    int min = arr[0];
    for(int i = 1; i < len; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    printf("Indices of minimum values: ");
    for(int i = 0; i < len; i++) {
        if(arr[i] == min) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {4, 2, 9, 2, 0, 3, 0, 3, 0, 2};
    int len = sizeof(arr) / sizeof(arr[0]);
    find_min_indices(arr, len);
    return 0;
}