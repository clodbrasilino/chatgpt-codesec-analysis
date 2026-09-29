#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

static int radix_sort(unsigned int *arr, size_t n)
{
    if (arr == NULL || n < 2) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(unsigned int)) {
        fprintf(stderr, "Array size too large\n");
        return -1;
    }

    unsigned int *temp = malloc(n * sizeof(unsigned int));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    unsigned int max_val = arr[0];
    for (size_t i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    for (unsigned int exp = 1; max_val / exp > 0; exp *= 10) {
        size_t count[10] = {0};

        for (size_t i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (size_t i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (size_t i = n; i-- > 0;) {
            unsigned int digit = (arr[i] / exp) % 10;
            temp[--count[digit]] = arr[i];
        }

        size_t copy_size = n * sizeof(unsigned int);
        /* Possible weaknesses found:
         *  The comparison 'copy_size <= sizeof(unsigned int)*n' is always true because 'copy_size' and 'sizeof(unsigned int)*n' represent the same value. [knownConditionTrueFalse]
         */
        if (copy_size / sizeof(unsigned int) == n && copy_size <= sizeof(unsigned int) * n) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(arr, temp, copy_size);
        }
    }

    free(temp);
    return 0;
}

int main(void)
{
    unsigned int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    for (size_t i = 0; i < n; i++) {
        printf("%u ", arr[i]);
    }
    printf("\n");

    if (radix_sort(arr, n) != 0) {
        fprintf(stderr, "Sort failed\n");
        return 1;
    }

    printf("Sorted array:\n");
    for (size_t i = 0; i < n; i++) {
        printf("%u ", arr[i]);
    }
    printf("\n");

    return 0;
}