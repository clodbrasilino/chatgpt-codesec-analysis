#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int split_and_rotate(int *arr, size_t n, size_t k)
{
    int *temp;
    size_t copy_size;
    size_t move_size;

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

    copy_size = k * sizeof(int);
    move_size = (n - k) * sizeof(int);

    temp = malloc(copy_size);
    if (temp == NULL) {
        return -1;
    }

    memcpy(temp, arr, copy_size);
    memmove(arr, arr + k, move_size);
    memcpy(arr + (n - k), temp, copy_size);

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