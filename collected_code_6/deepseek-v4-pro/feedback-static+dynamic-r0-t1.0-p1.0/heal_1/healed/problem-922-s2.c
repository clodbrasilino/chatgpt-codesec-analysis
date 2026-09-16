#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void findHighestProductPair(const int arr[], int n, int *first, int *second) {
    if (n < 2 || arr == NULL || first == NULL || second == NULL) {
        if (first != NULL) {
            *first = 0;
        }
        if (second != NULL) {
            *second = 0;
        }
        return;
    }

    int max1 = INT_MIN, max2 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
        }

        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } else if (arr[i] < min2) {
            min2 = arr[i];
        }
    }

    long long product_max = (long long)max1 * max2;
    long long product_min = (long long)min1 * min2;

    if (product_max >= product_min) {
        *first = max1;
        *second = max2;
    } else {
        *first = min1;
        *second = min2;
    }
}

int main(void) {
    int arr[] = {1, -4, 3, -6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int first = 0, second = 0;

    findHighestProductPair(arr, n, &first, &second);

    printf("%d %d\n", first, second);

    return 0;
}