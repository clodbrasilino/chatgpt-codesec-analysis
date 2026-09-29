#include <stdio.h>
#include <stdlib.h>

long long min_swaps_binary(int *arr, int n) {
    int total_ones = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            total_ones++;
        }
    }
    if (total_ones == 0 || total_ones == n) {
        return 0;
    }
    int current_ones = 0;
    for (int i = 0; i < total_ones; i++) {
        if (arr[i] == 1) {
            current_ones++;
        }
    }
    int max_ones = current_ones;
    for (int i = total_ones; i < n; i++) {
        if (arr[i] == 1) {
            current_ones++;
        }
        if (arr[i - total_ones] == 1) {
            current_ones--;
        }
        if (current_ones > max_ones) {
            max_ones = current_ones;
        }
    }
    return (long long)(total_ones - max_ones);
}

int main(void) {
    int arr1[] = {1, 0, 1, 0, 1, 0, 0, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    long long res1 = min_swaps_binary(arr1, n1);
    printf("%lld\n", res1);
    int arr2[] = {0, 0, 0, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    long long res2 = min_swaps_binary(arr2, n2);
    printf("%lld\n", res2);
    int arr3[] = {1, 1, 1, 0};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    long long res3 = min_swaps_binary(arr3, n3);
    printf("%lld\n", res3);
    return 0;
}