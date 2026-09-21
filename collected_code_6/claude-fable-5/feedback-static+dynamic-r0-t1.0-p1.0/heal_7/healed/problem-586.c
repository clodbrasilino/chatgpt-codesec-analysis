#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int safe_copy(void *dest, size_t dest_size, const void *src, size_t copy_size)
{
    unsigned char *d;
    const unsigned char *s;
    size_t i;

    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (copy_size == 0) {
        return 0;
    }
    if (copy_size > dest_size) {
        return -1;
    }

    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    for (i = 0; i < copy_size; i++) {
        d[i] = s[i];
    }
    return 0;
}

int split_and_rotate(int *arr, size_t n, size_t k)
{
    int *temp;
    size_t copy_size;
    size_t move_size;
    size_t total_size;

    if (arr == NULL || n == 0) {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    total_size = n * sizeof(int);

    k = k % n;
    if (k == 0) {
        return 0;
    }

    copy_size = k * sizeof(int);
    move_size = (n - k) * sizeof(int);

    if (copy_size > total_size || move_size > total_size) {
        return -1;
    }

    if (copy_size + move_size != total_size) {
        return -1;
    }

    temp = malloc(copy_size);
    if (temp == NULL) {
        return -1;
    }

    if (safe_copy(temp, copy_size, arr, copy_size) != 0) {
        free(temp);
        return -1;
    }

    memmove(arr, arr + k, move_size);

    if (safe_copy(arr + (n - k), total_size - move_size, temp, copy_size) != 0) {
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