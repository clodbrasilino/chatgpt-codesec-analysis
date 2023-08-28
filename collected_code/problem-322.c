#include <stdio.h>

void findMinIndex(int arr[], int n) {
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] == min) {
            printf("%d ", i);
        }
    }
}

int main() {
    int arr[] = {10, 3, 5, 2, 10, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Index positions of minimum values: ");
    findMinIndex(arr, n);
    return 0;
}