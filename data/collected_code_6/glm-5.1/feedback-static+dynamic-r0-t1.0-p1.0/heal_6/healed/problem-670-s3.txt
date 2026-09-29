#include <stdio.h>
#include <stdbool.h>

bool has_decreasing_trend(const int *seq, size_t len) {
    if (seq == NULL || len == 0) {
        return false;
    }

    if (len == 1) {
        return true;
    }

    for (size_t i = 1; i < len; ++i) {
        if (seq[i] >= seq[i - 1]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const int arr1[] = {5, 4, 3, 2, 1};
    const int arr2[] = {1, 2, 3, 4, 5};
    const int arr3[] = {5, 5, 3, 2, 1};
    const int arr4[] = {5};
    const int arr5[] = {10, 8, 6, 4, 2, 0, -2};
    const int arr6[] = {7, 6, 5, 4, 3};

    printf("%s\n", has_decreasing_trend(arr1, sizeof(arr1) / sizeof(arr1[0])) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(arr2, sizeof(arr2) / sizeof(arr2[0])) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(arr3, sizeof(arr3) / sizeof(arr3[0])) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(arr4, sizeof(arr4) / sizeof(arr4[0])) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(arr5, sizeof(arr5) / sizeof(arr5[0])) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(arr6, sizeof(arr6) / sizeof(arr6[0])) ? "True" : "False");

    return 0;
}