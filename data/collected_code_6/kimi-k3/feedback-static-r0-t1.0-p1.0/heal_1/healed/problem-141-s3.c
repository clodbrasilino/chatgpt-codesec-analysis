#include <stdio.h>
#include <stdlib.h>

static void flip(int *arr, size_t n) {
    size_t i;

    if (arr == NULL) {
        return;
    }

    for (i = 0; i < n / 2; ++i) {
        int tmp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = tmp;
    }
}

static size_t find_max_index(const int *arr, size_t n) {
    size_t i;
    size_t max_idx = 0;

    if (arr == NULL || n == 0) {
        return 0;
    }

    for (i = 1; i < n; ++i) {
        if (arr[i] > arr[max_idx]) {
            max_idx = i;
        }
    }

    return max_idx;
}

static int pancake_sort(int *arr, size_t n) {
    size_t curr_size;

    if (arr == NULL) {
        return -1;
    }

    if (n < 2) {
        return 0;
    }

    for (curr_size = n; curr_size > 1; --curr_size) {
        size_t max_idx = find_max_index(arr, curr_size);

        if (max_idx != curr_size - 1) {
            if (max_idx != 0) {
                flip(arr, max_idx + 1);
            }
            flip(arr, curr_size);
        }
    }

    return 0;
}

int main(void) {
    int data[] = {23, 10, 20, 11, 12, 6, 7};
    size_t n = sizeof(data) / sizeof(data[0]);
    size_t i;

    if (pancake_sort(data, n) != 0) {
        fprintf(stderr, "pancake_sort failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; ++i) {
        if (printf("%d%s", data[i], (i + 1 < n) ? " " : "\n") < 0) {
            fprintf(stderr, "printf failed\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}