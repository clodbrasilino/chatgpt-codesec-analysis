#include <stdio.h>
#include <stdlib.h>

void multiply_adjacent(int *arr, int length, int *result) {
    for (int i = 0; i < length - 1; ++i) {
        result[i] = arr[i] * arr[i + 1];
    }
}

int main() {
    int arr[] = {2, 3, 4, 5, 6};
    int length = sizeof(arr) / sizeof(arr[0]);
    int *result = (int *)malloc((length - 1) * sizeof(int));
    if (result == NULL) {
        return 1;
    }

    multiply_adjacent(arr, length, result);

    for (int i = 0; i < length - 1; ++i) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}