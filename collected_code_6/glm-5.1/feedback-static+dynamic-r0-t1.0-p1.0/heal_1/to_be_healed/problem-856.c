#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long min_adj_swaps_binary(int *arr, int n) {
    int total_ones = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            total_ones++;
        }
    }

    if (total_ones <= 1) {
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
        if (arr[i - total_ones] == 1) {
            window_ones--;
        }
        if (arr[i] == 1) {
            window_ones++;
        }
        if (window_ones > max_window_ones) {
            max_window_ones = window_ones;
        }
    }

    long long swaps = (long long)total_ones - max_window_ones;

    int req = 1;
    for (int i = 0; i < n && req <= total_ones; i++) {
        if (arr[i] == 1) {
            swaps += (long long)i - req;
            req++;
        }
    }

    return swaps;
}

int main() {
    int arr1[] = {1, 0, 1, 0, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%lld\n", min_adj_swaps_binary(arr1, n1));

    int arr2[] = {0, 0, 1, 0, 1, 0, 1, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%lld\n", min_adj_swaps_binary(arr2, n2));

    int arr3[] = {0, 0, 0};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%lld\n", min_adj_swaps_binary(arr3, n3));

    return 0;
}