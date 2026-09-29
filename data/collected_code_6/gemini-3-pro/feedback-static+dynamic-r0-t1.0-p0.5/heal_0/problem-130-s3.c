#include <stdio.h>
#include <stdlib.h>

int findMaxFrequencyItem(const int *arr, size_t size, int *result) {
    if (arr == NULL || size == 0 || result == NULL) {
        return -1;
    }

    int max_count = 0;
    int max_item = arr[0];

    for (size_t i = 0; i < size; i++) {
        int count = 0;
        for (size_t j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            max_item = arr[i];
        }
    }

    *result = max_item;
    return 0;
}

int main(void) {
    int arr[] = {1, 3, 2, 1, 4, 1, 2, 3, 1, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = 0;

    if (findMaxFrequencyItem(arr, size, &result) == 0) {
        printf("Item with maximum frequency: %d\n", result);
    } else {
        printf("Error finding maximum frequency item.\n");
    }

    return 0;
}