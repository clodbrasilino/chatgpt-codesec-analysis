#include <stdio.h>
#include <stdlib.h>

void move_zeros_to_end(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[count++] = arr[i];
        }
    }
    while (count < n) {
        arr[count++] = 0;
    }
}

int main() {
    int arr[] = {1, 0, 2, 0, 3, 4, 0, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    move_zeros_to_end(arr, n);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}