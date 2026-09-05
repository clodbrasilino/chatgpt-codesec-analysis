#include <stdio.h>
#include <stdlib.h>

int longest_increasing_subsequence(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    int *tails = (int *)malloc(n * sizeof(int));
    if (tails == NULL) {
        return 0;
    }

    size_t length = 0;

    for (size_t i = 0; i < n; i++) {
        size_t lo = 0;
        size_t hi = length;
        while (lo < hi) {
            size_t mid = lo + (hi - lo) / 2;
            if (tails[mid] < arr[i]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        tails[lo] = arr[i];
        if (lo == length) {
            length++;
        }
    }

    free(tails);
    return (int)length;
}

int main(void) {
    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int result = longest_increasing_subsequence(arr, n);
    printf("%d\n", result);

    return 0;
}