#include <stdio.h>
#include <stddef.h>

int findMaxProductPair(const int arr[], size_t n, int *first, int *second) {
    if (arr == NULL || n < 2 || first == NULL || second == NULL) {
        return -1;
    }

    int max1 = arr[0] > arr[1] ? arr[0] : arr[1];
    int max2 = arr[0] > arr[1] ? arr[1] : arr[0];
    int min1 = arr[0] < arr[1] ? arr[0] : arr[1];
    int min2 = arr[0] < arr[1] ? arr[1] : arr[0];

    for (size_t i = 2; i < n; ++i) {
        int val = arr[i];

        if (val > max1) {
            max2 = max1;
            max1 = val;
        } else if (val > max2) {
            max2 = val;
        }

        if (val < min1) {
            min2 = min1;
            min1 = val;
        } else if (val < min2) {
            min2 = val;
        }
    }

    long long prodMax = (long long)max1 * max2;
    long long prodMin = (long long)min1 * min2;

    if (prodMax >= prodMin) {
        *first = max1;
        *second = max2;
    } else {
        *first = min1;
        *second = min2;
    }

    return 0;
}

int main(void) {
    int arr[] = {-10, -20, 5, 2, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int a, b;

    if (findMaxProductPair(arr, n, &a, &b) == 0) {
        printf("%d %d\n", a, b);
    }

    return 0;
}