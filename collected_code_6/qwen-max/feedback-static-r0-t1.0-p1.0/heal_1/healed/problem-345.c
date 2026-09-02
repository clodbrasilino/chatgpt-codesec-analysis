#include <stdio.h>
#include <stdlib.h>

void findDifferences(const int *arr, int size, int *diff) {
    for (int i = 1; i < size; i++) {
        diff[i - 1] = arr[i] - arr[i - 1];
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int *diff = (int *)malloc((size - 1) * sizeof(int));
    if (diff == NULL) {
        return 1;
    }
    findDifferences(arr, size, diff);
    for (int i = 0; i < size - 1; i++) {
        printf("%d ", diff[i]);
    }
    free(diff);
    return 0;
}