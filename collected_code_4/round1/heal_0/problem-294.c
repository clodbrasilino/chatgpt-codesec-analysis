#include <stdio.h>

int findMax(int arr[], int n) {
    if (n < 1) {
        printf("Error: Empty array\n");
        return 0;
    }

    int max = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

int main() {
    int arr[] = {1, 45, 6, 89, 2, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = findMax(arr, n);

    printf("Max element in array: %d\n", max);

    return 0;
}