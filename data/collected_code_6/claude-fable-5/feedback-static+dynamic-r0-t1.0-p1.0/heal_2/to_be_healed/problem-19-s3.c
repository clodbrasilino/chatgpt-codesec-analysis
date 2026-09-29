#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

bool contains_duplicate(const int *arr, size_t size)
{
    int *copy;
    size_t i;
    size_t bytes;
    bool found;

    if (arr == NULL || size < 2) {
        return false;
    }

    if (size > SIZE_MAX / sizeof(*copy)) {
        fprintf(stderr, "Requested size too large\n");
        exit(EXIT_FAILURE);
    }

    bytes = size * sizeof(*copy);

    copy = malloc(bytes);
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, arr, bytes);
    qsort(copy, size, sizeof(*copy), compare_ints);

    found = false;
    for (i = 1; i < size; i++) {
        if (copy[i] == copy[i - 1]) {
            found = true;
            break;
        }
    }

    free(copy);
    return found;
}

int main(void)
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 2, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    if (contains_duplicate(arr1, size1)) {
        printf("Array 1 contains duplicates\n");
    } else {
        printf("Array 1 does not contain duplicates\n");
    }

    if (contains_duplicate(arr2, size2)) {
        printf("Array 2 contains duplicates\n");
    } else {
        printf("Array 2 does not contain duplicates\n");
    }

    return EXIT_SUCCESS;
}