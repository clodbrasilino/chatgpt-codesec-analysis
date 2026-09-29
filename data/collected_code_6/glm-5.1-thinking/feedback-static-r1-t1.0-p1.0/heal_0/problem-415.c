#include <stdio.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
    long long product;
} PairResult;

PairResult findHighestProductPair(int arr[], int size) {
    PairResult invalid = {0, 0, LLONG_MIN};

    if (size < 2) {
        return invalid;
    }

    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;

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

    long long product_max = (long long)max1 * max2;
    long long product_min = (long long)min1 * min2;

    PairResult result;
    if (product_max > product_min) {
        result.first = max1;
        result.second = max2;
        result.product = product_max;
    } else {
        result.first = min1;
        result.second = min2;
        result.product = product_min;
    }

    return result;
}

int main(void) {
    int arr1[] = {1, 4, 3, 6, 2, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    PairResult res1 = findHighestProductPair(arr1, size1);
    if (size1 >= 2) {
        printf("Pair: (%d, %d), Product: %lld\n", res1.first, res1.second, res1.product);
    }

    int arr2[] = {-10, -3, 5, 2, -9};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    PairResult res2 = findHighestProductPair(arr2, size2);
    if (size2 >= 2) {
        printf("Pair: (%d, %d), Product: %lld\n", res2.first, res2.second, res2.product);
    }

    int arr3[] = {5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    PairResult res3 = findHighestProductPair(arr3, size3);
    if (size3 < 2) {
        printf("No pair found.\n");
    }

    return 0;
}