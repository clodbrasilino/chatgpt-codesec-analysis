#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_min_heap(const int *arr, size_t n) {
    if (arr == NULL) {
        return false;
    }
    if (n == 0) {
        return true;
    }
    for (size_t i = 0; i < n / 2; i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        if (left < n && arr[i] > arr[left]) {
            return false;
        }
        if (right < n && arr[i] > arr[right]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    const int valid_heap[] = {1, 3, 2, 5, 4, 6};
    size_t valid_n = sizeof(valid_heap) / sizeof(valid_heap[0]);

    const int invalid_heap[] = {2, 1, 3};
    size_t invalid_n = sizeof(invalid_heap) / sizeof(invalid_heap[0]);

    const int *empty_arr = NULL;
    size_t empty_n = 0;

    if (is_min_heap(valid_heap, valid_n)) {
        printf("valid_heap: true\n");
    } else {
        printf("valid_heap: false\n");
    }

    if (is_min_heap(invalid_heap, invalid_n)) {
        printf("invalid_heap: true\n");
    } else {
        printf("invalid_heap: false\n");
    }

    if (is_min_heap(empty_arr, empty_n)) {
        printf("empty_array: true\n");
    } else {
        printf("empty_array: false\n");
    }

    if (is_min_heap(NULL, 1)) {
        printf("null_array: true\n");
    } else {
        printf("null_array: false\n");
    }

    return EXIT_SUCCESS;
}