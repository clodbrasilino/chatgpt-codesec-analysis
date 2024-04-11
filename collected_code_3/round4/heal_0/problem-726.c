#include <stdio.h>

void multiply_adjacent_elements(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        printf("%d ", arr[i] * arr[i+1]);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    multiply_adjacent_elements(arr, n);

    return 0;
}