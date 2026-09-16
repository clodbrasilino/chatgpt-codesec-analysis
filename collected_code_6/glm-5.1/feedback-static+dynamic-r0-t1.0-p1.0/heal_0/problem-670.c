#include <stdio.h>
#include <stdlib.h>

int has_decreasing_trend(const int *seq, size_t len) {
    if (seq == NULL || len <= 1) {
        return 0;
    }
    for (size_t i = 1; i < len; ++i) {
        if (seq[i] >= seq[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int arr1[] = {5, 4, 3, 2, 1};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {5, 5, 3, 2, 1};
    int arr4[] = {10};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);
    size_t len4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", has_decreasing_trend(arr1, len1));
    printf("%d\n", has_decreasing_trend(arr2, len2));
    printf("%d\n", has_decreasing_trend(arr3, len3));
    printf("%d\n", has_decreasing_trend(arr4, len4));
    printf("%d\n", has_decreasing_trend(NULL, len1));
    return 0;
}