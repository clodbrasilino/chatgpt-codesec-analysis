#include <stdio.h>
#include <stddef.h>

size_t max_sublist_length(const int arr[], size_t n);

size_t max_sublist_length(const int arr[], size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    size_t max_len = 1;
    size_t current_len = 1;

    for (size_t i = 1; i < n; ++i) {
        if (arr[i] == arr[i - 1]) {
            ++current_len;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 1;
        }
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    return max_len;
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("%zu\n", max_sublist_length(arr, n));

    return 0;
}