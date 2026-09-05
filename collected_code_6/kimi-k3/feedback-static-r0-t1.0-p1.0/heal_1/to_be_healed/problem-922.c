#include <stdio.h>
#include <limits.h>

void findMaxProductPair(const int arr[], int size, int *first, int *second, long long *product) {
    if (arr == NULL || first == NULL || second == NULL || product == NULL || size < 2) {
        if (first != NULL) *first = 0;
        if (second != NULL) *second = 0;
        if (product != NULL) *product = 0;
        return;
    }

    int max1 = INT_MIN, max2 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;

    for (int i = 0; i < size; i++) {
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

    long long productMax = (long long)max1 * max2;
    long long productMin = (long long)min1 * min2;

    if (productMax > productMin) {
        *first = max1;
        *second = max2;
        *product = productMax;
    } else {
        *first = min1;
        *second = min2;
        *product = productMin;
    }
}

int main(void) {
    int arr[] = {1, 4, 3, -6, 7, 0};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(arr)/sizeof(arr[0])', assigned value is 6
     */
    int size = sizeof(arr) / sizeof(arr[0]);
    int first = 0, second = 0;
    long long product = 0;

    findMaxProductPair(arr, size, &first, &second, &product);

    /* Possible weaknesses found:
     *  Condition 'size>=2' is always true
     *  Condition 'size>=2' is always true [knownConditionTrueFalse]
     */
    if (size >= 2) {
        printf("Pair: (%d, %d)\n", first, second);
        printf("Product: %lld\n", product);
    } else {
        printf("Array must contain at least two elements.\n");
    }

    return 0;
}