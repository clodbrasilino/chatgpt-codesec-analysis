#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void find_highest_product_pair(const int *arr, size_t n, int *ans1, int *ans2) {
    if (n < 2 || arr == NULL || ans1 == NULL || ans2 == NULL) {
        return;
    }

    int max1 = INT_MIN, max2 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;

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

    long long prod_max = (long long)max1 * max2;
    long long prod_min = (long long)min1 * min2;

    if (prod_max > prod_min) {
        *ans1 = max1;
        *ans2 = max2;
    } else {
        *ans1 = min1;
        *ans2 = min2;
    }
}

int main(void) {
    int arr[] = {1, 4, 3, 6, 7, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    int ans1 = 0;
    int ans2 = 0;

    find_highest_product_pair(arr, n, &ans1, &ans2);

    printf("Pair with highest product: %d and %d\n", ans1, ans2);

    return EXIT_SUCCESS;
}