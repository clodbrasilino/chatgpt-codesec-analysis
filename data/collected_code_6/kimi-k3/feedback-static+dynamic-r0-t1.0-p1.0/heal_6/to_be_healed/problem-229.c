#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

void rearrange(int *arr, size_t n)
{
    if (arr == NULL || n == 0) {
        return;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        return;
    }

    int *temp = malloc(n * sizeof(int));
    if (temp == NULL) {
        return;
    }

    size_t idx = 0;

    for (size_t i = 0; i < n && idx < n; i++) {
        if (arr[i] < 0) {
            temp[idx++] = arr[i];
        }
    }

    for (size_t i = 0; i < n && idx < n; i++) {
        if (arr[i] >= 0) {
            temp[idx++] = arr[i];
        }
    }

    if (idx == n) {
        /* Possible weaknesses found:
         *  'copy_size' is assigned value 'n*sizeof(int)' here.
         */
        size_t copy_size = n * sizeof(int);
        /* Possible weaknesses found:
         *  The comparison 'copy_size <= n*sizeof(int)' is always true because 'copy_size' and 'n*sizeof(int)' represent the same value.
         *  The comparison 'copy_size <= n*sizeof(int)' is always true because 'copy_size' and 'n*sizeof(int)' represent the same value. [knownConditionTrueFalse]
         */
        if (copy_size / sizeof(int) == n && copy_size <= n * sizeof(int)) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(arr, temp, copy_size);
        }
    }

    free(temp);
}

int main(void)
{
    int arr[] = {12, -3, 5, -7, -1, 8, -4, 0, 6, -9};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    rearrange(arr, n);

    printf("Rearranged array:\n");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}