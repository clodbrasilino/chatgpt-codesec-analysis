#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int split_and_rotate(int *arr, size_t n, size_t k)
{
    int *temp;

    if (arr == NULL || n == 0) {
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

    memcpy(temp, arr, k * sizeof(int));
    memmove(arr, arr + k, (n - k) * sizeof(int));
    memcpy(arr + (n - k), temp, k * sizeof(int));

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