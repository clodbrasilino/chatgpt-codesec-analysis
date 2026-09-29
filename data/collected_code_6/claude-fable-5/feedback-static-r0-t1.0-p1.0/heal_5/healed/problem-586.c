#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int split_and_rotate(int *arr, size_t n, size_t k)
{
    int *temp;
    size_t head_bytes;
    size_t tail_bytes;
    size_t total_bytes;

    if (arr == NULL || n == 0) {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    total_bytes = n * sizeof(int);

    k = k % n;
    if (k == 0) {
        return 0;
    }

    if (k > n || (n - k) > n) {
        return -1;
    }

    head_bytes = k * sizeof(int);
    tail_bytes = (n - k) * sizeof(int);

    if (head_bytes > total_bytes || tail_bytes > total_bytes) {
        return -1;
    }

    if (head_bytes + tail_bytes != total_bytes) {
        return -1;
    }

    temp = malloc(head_bytes);
    if (temp == NULL) {
        return -1;
    }

    if (head_bytes > total_bytes) {
        free(temp);
        return -1;
    }
    memcpy(temp, arr, head_bytes);

    if (tail_bytes > total_bytes) {
        free(temp);
        return -1;
    }
    memmove(arr, arr + k, tail_bytes);

    if ((n - k) > n || head_bytes > total_bytes - tail_bytes) {
        free(temp);
        return -1;
    }
    memcpy(arr + (n - k), temp, head_bytes);

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
        fprintf(stderr, "Error: rotation failed\n");
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