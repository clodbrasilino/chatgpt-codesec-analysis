#include <stdio.h>
#include <stdlib.h>

int check_pattern(const int *arr, size_t arr_size, const int *patterns, size_t pat_size) {
    if (arr == NULL || patterns == NULL) {
        return 0;
    }
    if (arr_size == 0 && pat_size == 0) {
        return 1;
    }
    if (arr_size == 0 || pat_size == 0) {
        return 0;
    }

    size_t arr_idx = 0;
    size_t pat_idx = 0;

    while (arr_idx < arr_size && pat_idx < pat_size) {
        size_t match_len = 0;
        while (arr_idx + match_len < arr_size && match_len < (size_t)patterns[pat_idx] && arr[arr_idx + match_len] == patterns[pat_idx]) {
            match_len++;
        }
        if (match_len != (size_t)patterns[pat_idx]) {
            return 0;
        }
        arr_idx += match_len;
        pat_idx++;
    }

    return arr_idx == arr_size && pat_idx == pat_size;
}

int main(void) {
    int arr1[] = {1, 1, 2, 2, 2, 3};
    int pat1[] = {2, 3, 1};
    printf("%d\n", check_pattern(arr1, sizeof(arr1)/sizeof(arr1[0]), pat1, sizeof(pat1)/sizeof(pat1[0])));

    int arr2[] = {1, 1, 2, 2, 2, 3, 3};
    int pat2[] = {2, 3, 2};
    printf("%d\n", check_pattern(arr2, sizeof(arr2)/sizeof(arr2[0]), pat2, sizeof(pat2)/sizeof(pat2[0])));

    int arr3[] = {4, 4, 4, 4};
    int pat3[] = {4};
    printf("%d\n", check_pattern(arr3, sizeof(arr3)/sizeof(arr3[0]), pat3, sizeof(pat3)/sizeof(pat3[0])));

    int arr4[] = {1, 2, 3};
    int pat4[] = {1, 1, 1};
    printf("%d\n", check_pattern(arr4, sizeof(arr4)/sizeof(arr4[0]), pat4, sizeof(pat4)/sizeof(pat4[0])));

    printf("%d\n", check_pattern(NULL, 0, pat1, sizeof(pat1)/sizeof(pat1[0])));
    printf("%d\n", check_pattern(arr1, sizeof(arr1)/sizeof(arr1[0]), NULL, 0));

    return 0;
}