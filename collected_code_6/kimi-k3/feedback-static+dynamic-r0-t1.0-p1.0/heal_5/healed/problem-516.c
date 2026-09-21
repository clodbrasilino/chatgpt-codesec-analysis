#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
        if (copy_size / sizeof(unsigned int) == n) {
            if (copy_size > n * sizeof(unsigned int)) {
                fprintf(stderr, "Buffer overflow detected\n");
                free(temp);
                return -1;
            }
            memcpy(arr, temp, copy_size);
        } else {
            fprintf(stderr, "Integer overflow detected during copy size calculation\n");
            free(temp);
            return -1;
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