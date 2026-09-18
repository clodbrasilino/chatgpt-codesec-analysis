#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void findHighestProductPair(const int arr[], int n, int *result1, int *result2) {
    if (n < 2) {
        *result1 = 0;
        *result2 = 0;
        return;
    }

    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;

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

    if ((long long)max1 * max2 > (long long)min1 * min2) {
        *result1 = max1;
        *result2 = max2;
    } else {
        *result1 = min1;
        *result2 = min2;
    }
}

int main(void) {
    const int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result1 = 0;
    int result2 = 0;

    findHighestProductPair(arr, n, &result1, &result2);

    printf("Pair with highest product: %d, %d\n", result1, result2);

    return 0;
}