#include <stdio.h>
#include <stdlib.h>

int findSmallestMissing(int arr[], int size) {
    int *present = (int *)calloc(size + 1, sizeof(int));
    if (present == NULL) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] > 0 && arr[i] <= size) {
            present[arr[i]] = 1;
        }
    }

    for (int i = 1; i <= size; i++) {
        if (!present[i]) {
            free(present);
            return i;
        }
    }

    free(present);
    return size + 1;
}

int main(void) {
    int arr[] = {1, 3, 6, 4, 1, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    int missing = findSmallestMissing(arr, size);
    if (missing == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Smallest missing number: %d\n", missing);

    return 0;
}