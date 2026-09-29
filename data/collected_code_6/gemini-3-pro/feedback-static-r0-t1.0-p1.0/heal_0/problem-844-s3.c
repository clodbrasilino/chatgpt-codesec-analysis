#include <stdio.h>
#include <stdlib.h>

int findKthElement(const int *arr, size_t size, size_t k, int *result) {
    if (arr == NULL || k == 0 || k > size || result == NULL) {
        return -1;
    }

    size_t oddCount = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 != 0) {
            oddCount++;
        }
    }

    if (k <= oddCount) {
        size_t currentOdd = 0;
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] % 2 != 0) {
                currentOdd++;
                if (currentOdd == k) {
                    *result = arr[i];
                    return 0;
                }
            }
        }
    } else {
        size_t currentEven = 0;
        size_t targetEven = k - oddCount;
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] % 2 == 0) {
                currentEven++;
                if (currentEven == targetEven) {
                    *result = arr[i];
                    return 0;
                }
            }
        }
    }

    return -1;
}

int main(void) {
    int arr[] = {3, 1, 7, 5, 2, 8, 6, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t k = 6;
    int result = 0;

    if (findKthElement(arr, size, k, &result) == 0) {
        printf("%d\n", result);
    } else {
        printf("Error: Invalid inputs or element not found.\n");
    }

    return 0;
}