#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void find_max_product_pair(const int *arr, int n, int *max1, int *max2) {
    if (arr == NULL || n < 2 || max1 == NULL || max2 == NULL) {
        return;
    }

    int max_a = INT_MIN;
    int max_b = INT_MIN;
    int min_a = INT_MAX;
    int min_b = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max_a) {
            max_b = max_a;
            max_a = arr[i];
        } else if (arr[i] > max_b) {
            max_b = arr[i];
        }

        if (arr[i] < min_a) {
            min_b = min_a;
            min_a = arr[i];
        } else if (arr[i] < min_b) {
            min_b = arr[i];
        }
    }

    long long prod1 = (long long)max_a * max_b;
    long long prod2 = (long long)min_a * min_b;

    if (prod1 > prod2) {
        *max1 = max_a;
        *max2 = max_b;
    } else {
        *max1 = min_a;
        *max2 = min_b;
    }
}

int main() {
    int arr[] = {1, -4, 3, -6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    int val1, val2;
    find_max_product_pair(arr, n, &val1, &val2);

    printf("%d %d\n", val1, val2);

    return 0;
}