#include <stdio.h>
#include <limits.h>

long long findMaxProductPair(const int arr[], int n, int *first, int *second) {
    if (arr == NULL || n < 2 || first == NULL || second == NULL) {
        if (first != NULL) {
            *first = 0;
        }
        if (second != NULL) {
            *second = 0;
        }
        return LLONG_MIN;
    }

    int min1 = INT_MAX, min2 = INT_MAX;
    int max1 = INT_MIN, max2 = INT_MIN;

    for (int i = 0; i < n; i++) {
        int value = arr[i];

        if (value > max1) {
            max2 = max1;
            max1 = value;
        } else if (value > max2) {
            max2 = value;
        }

        if (value < min1) {
            min2 = min1;
            min1 = value;
        } else if (value < min2) {
            min2 = value;
        }
    }

    long long productMax = (long long)max1 * max2;
    long long productMin = (long long)min1 * min2;

    if (productMax >= productMin) {
        *first = max1;
        *second = max2;
        return productMax;
    } else {
        *first = min1;
        *second = min2;
        return productMin;
    }
}

int main(void) {
    int arr[] = {-10, -8, 2, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int first, second;
    long long product = findMaxProductPair(arr, n, &first, &second);

    printf("%d %d %lld\n", first, second, product);

    return 0;
}