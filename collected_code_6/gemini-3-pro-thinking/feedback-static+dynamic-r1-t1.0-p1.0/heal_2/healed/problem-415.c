#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int find_highest_product_pair(const int *arr, size_t size, int *out_first, int *out_second) {
    if (arr == NULL || size < 2 || out_first == NULL || out_second == NULL) {
        return -1;
    }

    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;

    for (size_t i = 0; i < size; i++) {
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

    long long prod_max = (long long)max1 * (long long)max2;
    long long prod_min = (long long)min1 * (long long)min2;

    if (prod_max >= prod_min) {
        *out_first = max1;
        *out_second = max2;
    } else {
        *out_first = min1;
        *out_second = min2;
    }

    return 0;
}

int main(void) {
    int arr1[] = {1, 4, 3, 6, 7, 0};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int first = 0;
    int second = 0;

    if (find_highest_product_pair(arr1, size1, &first, &second) == 0) {
        printf("Pair 1: %d, %d\n", first, second);
    } else {
        printf("Error processing arr1\n");
    }

    int arr2[] = {-10, -3, 5, 6, -20};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    if (find_highest_product_pair(arr2, size2, &first, &second) == 0) {
        printf("Pair 2: %d, %d\n", first, second);
    } else {
        printf("Error processing arr2\n");
    }

    int arr3[] = {-5};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    if (find_highest_product_pair(arr3, size3, &first, &second) == 0) {
        printf("Pair 3: %d, %d\n", first, second);
    } else {
        printf("Error processing arr3: insufficient elements\n");
    }

    return 0;
}