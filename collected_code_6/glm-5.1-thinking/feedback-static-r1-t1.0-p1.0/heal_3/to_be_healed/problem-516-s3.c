#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

void radix_sort(int *arr, size_t n) {
    if (arr == NULL || n <= 1) {
        return;
    }

    if (n > SIZE_MAX / sizeof(unsigned int)) {
        return;
    }

    size_t alloc_size = n * sizeof(unsigned int);

    unsigned int *data = malloc(alloc_size);
    if (data == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(data, arr, alloc_size);

    unsigned int flip_mask = (UINT_MAX >> 1) + 1;

    for (size_t i = 0; i < n; i++) {
        data[i] ^= flip_mask;
    }

    unsigned int *temp = malloc(alloc_size);
    if (temp == NULL) {
        free(data);
        return;
    }

    size_t total_bits = sizeof(int) * CHAR_BIT;

    for (size_t shift = 0; shift < total_bits; shift += 8) {
        size_t count[256] = {0};

        for (size_t i = 0; i < n; i++) {
            count[(data[i] >> shift) & 0xFF]++;
        }

        for (size_t i = 1; i < 256; i++) {
            count[i] += count[i - 1];
        }

        for (size_t i = n; i > 0; i--) {
            temp[--count[(data[i - 1] >> shift) & 0xFF]] = data[i - 1];
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(data, temp, alloc_size);
    }

    for (size_t i = 0; i < n; i++) {
        data[i] ^= flip_mask;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arr, data, alloc_size);

    free(data);
    free(temp);
}

int main(void) {
    int arr[] = {170, 45, 75, -90, -802, 24, 2, 66, -1, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, n);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}