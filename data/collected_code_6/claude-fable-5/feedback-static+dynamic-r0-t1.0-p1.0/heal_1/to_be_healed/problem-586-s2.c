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

    temp = malloc(k * sizeof(*temp));
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, arr, k * sizeof(*temp));
    memmove(arr, arr + k, (n - k) * sizeof(*arr));
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arr + (n - k), temp, k * sizeof(*temp));

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