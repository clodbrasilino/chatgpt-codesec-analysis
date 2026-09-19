#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_peak_element(const int *arr, int n) {
    if (n <= 0 || arr == NULL) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long left_val = (mid > 0) ? (long)arr[mid - 1] : LONG_MIN;
        long right_val = (mid < n - 1) ? (long)arr[mid + 1] : LONG_MIN;
        long mid_val = (long)arr[mid];
        if (mid_val >= left_val && mid_val >= right_val) {
            return mid;
        } else if (right_val > mid_val) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = argc - 1;
    int *arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    int peak_index = find_peak_element(arr, n);
    printf("%d\n", peak_index);
    free(arr);
    arr = NULL;
    return 0;
}