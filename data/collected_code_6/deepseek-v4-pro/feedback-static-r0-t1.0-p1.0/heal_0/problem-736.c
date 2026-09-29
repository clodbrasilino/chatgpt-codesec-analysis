#include <stddef.h>

size_t bisect_left(int *arr, size_t n, int value) {
    size_t lo = 0;
    size_t hi = n;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (arr[mid] < value) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

#include <stdio.h>

int main(void) {
    int arr[] = {1, 2, 4, 4, 5, 7, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int values[] = {0, 1, 4, 6, 9, 10};
    size_t m = sizeof(values) / sizeof(values[0]);
    for (size_t i = 0; i < m; ++i) {
        size_t pos = bisect_left(arr, n, values[i]);
        printf("bisect_left(%d) = %zu\n", values[i], pos);
    }
    return 0;
}