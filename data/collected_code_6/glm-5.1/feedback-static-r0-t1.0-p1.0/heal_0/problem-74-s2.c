#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool follows_pattern(const int *arr, size_t arr_len, const int *patterns, size_t patterns_len) {
    if (arr == NULL || patterns == NULL) {
        return false;
    }

    if (patterns_len == 0) {
        return true;
    }

    size_t pattern_idx = 0;

    for (size_t i = 0; i < arr_len; i++) {
        if (arr[i] == patterns[pattern_idx]) {
            pattern_idx++;
            if (pattern_idx == patterns_len) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int patterns1[] = {2, 4};
    
    bool res1 = follows_pattern(arr1, sizeof(arr1) / sizeof(arr1[0]), patterns1, sizeof(patterns1) / sizeof(patterns1[0]));
    printf("%d\n", res1);

    int arr2[] = {1, 2, 3, 4, 5};
    int patterns2[] = {4, 2};
    
    bool res2 = follows_pattern(arr2, sizeof(arr2) / sizeof(arr2[0]), patterns2, sizeof(patterns2) / sizeof(patterns2[0]));
    printf("%d\n", res2);

    int arr3[] = {1, 2, 3};
    int patterns3[] = {1, 2, 3, 4};
    
    bool res3 = follows_pattern(arr3, sizeof(arr3) / sizeof(arr3[0]), patterns3, sizeof(patterns3) / sizeof(patterns3[0]));
    printf("%d\n", res3);

    bool res4 = follows_pattern(NULL, 0, patterns1, sizeof(patterns1) / sizeof(patterns1[0]));
    printf("%d\n", res4);

    bool res5 = follows_pattern(arr1, sizeof(arr1) / sizeof(arr1[0]), NULL, 0);
    printf("%d\n", res5);

    return 0;
}