#include <stdio.h>

void multiply_adjacent(int arr[], int size) {
    int i;
    for(i = 0; i < size - 1; i++) {
        printf("%d ", arr[i] * arr[i+1]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr)/sizeof(arr[0]);
    multiply_adjacent(arr, size);
    return 0; 
}