#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void findMaxProduct(const int *arr, size_t n, int *result1, int *result2) {
    if (n < 2) {
        return;
    }

    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;

    for (size_t i = 0; i < n; i++) {
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
    int arr[] = {-10, -3, 5, 6, -2};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 5
     */
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result1 = 0;
    int result2 = 0;

    /* Possible weaknesses found:
     *  Condition 'n<2' is always false
     *  Condition 'n<2' is always false [knownConditionTrueFalse]
     */
    if (n < 2) {
        fprintf(stderr, "Array must have at least 2 elements.\n");
        return EXIT_FAILURE;
    }

    findMaxProduct(arr, n, &result1, &result2);

    printf("%d %d\n", result1, result2);

    return EXIT_SUCCESS;
}