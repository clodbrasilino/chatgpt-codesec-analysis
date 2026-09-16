#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_product_pair(const int *arr, size_t size, int *out_pair) {
    if (arr == NULL || out_pair == NULL) {
        return -1;
    }

    if (size < 2) {
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

    long long prod1 = (long long)max1 * max2;
    long long prod2 = (long long)min1 * min2;

    if (prod1 > prod2) {
        out_pair[0] = max1;
        out_pair[1] = max2;
    } else {
        out_pair[0] = min1;
        out_pair[1] = min2;
    }

    return 0;
}

int main(void) {
    int arr[] = {-10, -3, 5, 6, -20};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int pair[2] = {0};

    int status = find_max_product_pair(arr, size, pair);

    if (status == 0) {
        printf("Pair with the highest product: {%d, %d}\n", pair[0], pair[1]);
    } else {
        fprintf(stderr, "Error: Invalid input or array too small.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}