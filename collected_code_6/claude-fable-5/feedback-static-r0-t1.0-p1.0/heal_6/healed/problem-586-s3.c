#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int checked_copy(int *dst, size_t dst_count,
                        const int *src, size_t src_count)
{
    size_t i;

    if (dst == NULL || src == NULL) {
        return -1;
    }
    if (src_count > dst_count) {
        return -1;
    }
    for (i = 0; i < src_count; i++) {
        dst[i] = src[i];
    }
    return 0;
}

static int checked_move(int *dst, size_t dst_count,
                        const int *src, size_t src_count)
{
    size_t i;

    if (dst == NULL || src == NULL) {
        return -1;
    }
    if (src_count > dst_count) {
        return -1;
    }
    if (dst <= src) {
        for (i = 0; i < src_count; i++) {
            dst[i] = src[i];
        }
    } else {
        for (i = src_count; i > 0; i--) {
            dst[i - 1] = src[i - 1];
        }
    }
    return 0;
}

int split_and_rotate(int *arr, size_t n, size_t k)
{
    int *temp;

    if (arr == NULL || n == 0) {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    k = k % n;
    if (k == 0) {
        return 0;
    }

    temp = malloc(k * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    if (checked_copy(temp, k, arr, k) != 0) {
        free(temp);
        return -1;
    }

    if (checked_move(arr, n, arr + k, n - k) != 0) {
        free(temp);
        return -1;
    }

    if (checked_copy(arr + (n - k), k, temp, k) != 0) {
        free(temp);
        return -1;
    }

    free(temp);
    return 0;
}

int main(void)
{
    int arr[] = {12, 10, 5, 6, 52, 36};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 2;
    size_t i;

    if (split_and_rotate(arr, n, k) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}