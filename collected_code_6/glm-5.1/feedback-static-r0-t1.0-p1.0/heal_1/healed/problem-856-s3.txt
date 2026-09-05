#include <stdio.h>
#include <stdlib.h>

long long min_swaps_binary(const int *arr, int n) {
    int total_ones = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            total_ones++;
        }
    }

    if (total_ones == 0 || total_ones == n) {
        return 0;
    }

    int window_ones = 0;
    for (int i = 0; i < total_ones; i++) {
        if (arr[i] == 1) {
            window_ones++;
        }
    }

    int max_window_ones = window_ones;

    for (int i = total_ones; i < n; i++) {
        if (arr[i] == 1) {
            window_ones++;
        }
        if (arr[i - total_ones] == 1) {
            window_ones--;
        }
        if (window_ones > max_window_ones) {
            max_window_ones = window_ones;
        }
    }

    return (long long)total_ones - max_window_ones;
}

int main(void) {
    int arr1[] = {1, 0, 1, 0, 1, 0, 0, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%lld\n", min_swaps_binary(arr1, n1));

    int arr2[] = {0, 0, 0, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%lld\n", min_swaps_binary(arr2, n2));

    int arr3[] = {1, 1, 1, 0};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%lld\n", min_swaps_binary(arr3, n3));

    int arr4[] = {0, 0, 0, 0};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%lld\n", min_swaps_binary(arr4, n4));

    return 0;
}