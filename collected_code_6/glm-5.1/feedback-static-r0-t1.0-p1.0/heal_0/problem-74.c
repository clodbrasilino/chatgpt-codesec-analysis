#include <stdlib.h>
#include <stdbool.h>

bool check_sequence(const int *arr, size_t arr_len, const int *patterns, size_t patterns_len) {
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
    int pat1[] = {2, 4};
    bool res1 = check_sequence(arr1, 5, pat1, 2);

    int arr2[] = {1, 2, 3, 4, 5};
    int pat2[] = {4, 2};
    bool res2 = check_sequence(arr2, 5, pat2, 2);

    int arr3[] = {1, 2, 3, 4, 5};
    int pat3[] = {1, 2, 3, 4, 5};
    bool res3 = check_sequence(arr3, 5, pat3, 5);

    int arr4[] = {1, 2, 3, 4, 5};
    int pat4[] = {0};
    bool res4 = check_sequence(arr4, 5, pat4, 0);

    bool res5 = check_sequence(NULL, 0, pat1, 2);
    bool res6 = check_sequence(arr1, 5, NULL, 2);

    (void)res1;
    (void)res2;
    (void)res3;
    (void)res4;
    (void)res5;
    (void)res6;

    return 0;
}