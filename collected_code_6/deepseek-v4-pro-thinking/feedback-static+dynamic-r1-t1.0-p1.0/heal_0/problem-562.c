#include <stddef.h>
#include <stdio.h>

size_t max_sublist_length(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    size_t max_len = 1;
    size_t curr_len = 1;

    for (size_t i = 1; i < n; ++i) {
        if (arr[i] == arr[i - 1]) {
            ++curr_len;
        } else {
            if (curr_len > max_len) {
                max_len = curr_len;
            }
            curr_len = 1;
        }
    }

    if (curr_len > max_len) {
        max_len = curr_len;
    }

    return max_len;
}

int main(void) {
    int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 4, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    printf("%zu\n", max_sublist_length(arr, n));
    return 0;
}