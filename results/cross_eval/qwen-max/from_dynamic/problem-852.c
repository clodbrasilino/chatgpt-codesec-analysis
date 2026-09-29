#include <stdio.h>
#include <stdlib.h>

void removeNegatives(int *arr, int *n) {
    int j = 0;
    for (int i = 0; i < *n; i++) {
        if (arr[i] >= 0) {
            arr[j++] = arr[i];
        }
    }
    *n = j;
}

int main() {
    int arr[] = {-5, -1, 2, -3, 4, 6, -7};
    int n = sizeof(arr) / sizeof(arr[0]);

    removeNegatives(arr, &n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}