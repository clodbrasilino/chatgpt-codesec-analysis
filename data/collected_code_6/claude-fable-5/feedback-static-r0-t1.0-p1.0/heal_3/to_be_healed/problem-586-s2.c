#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int split_and_rotate(int *arr, size_t n, size_t k)
{
    int *temp;
    size_t temp_size;
    size_t move_size;

    if (arr == NULL || n == 0) {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(*arr)) {
        return -1;
    }

    k = k % n;
    if (k == 0) {
        return 0;
    }

    if (k > n) {
        return -1;
    }

    temp_size = k * sizeof(*temp);
    move_size = (n - k) * sizeof(*arr);

    if (temp_size > n * sizeof(*arr) || move_size > n * sizeof(*arr)) {
        return -1;
    }

    temp = malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, arr, temp_size);
    memmove(arr, arr + k, move_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arr + (n - k), temp, temp_size);

    free(temp);
    return 0;
}

void print_array(const int *arr, size_t n)
{
    size_t i;

    if (arr == NULL) {
        return;
    }

    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int arr[] = {12, 10, 5, 6, 52, 36};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 2;

    printf("Original array: ");
    print_array(arr, n);

    if (split_and_rotate(arr, n, k) != 0) {
        fprintf(stderr, "Error: rotation failed\n");
        return EXIT_FAILURE;
    }

    printf("Array after splitting at %zu and adding first part to end: ", k);
    print_array(arr, n);

    return EXIT_SUCCESS;
}