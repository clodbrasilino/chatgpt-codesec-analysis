#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define RADIX_BITS 8u
#define RADIX (1u << RADIX_BITS)
#define RADIX_MASK (RADIX - 1u)
#define SIGN_BIT (1u << (sizeof(unsigned int) * CHAR_BIT - 1u))

static void print_array(const int *arr, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", arr[i]);
    }
    putchar('\n');
}

static int radix_sort(int *arr, size_t n)
{
    int *tmp;
    int *src;
    int *dst;
    size_t passes;
    size_t pass;
    size_t bytes;

    if (arr == NULL) {
        return -1;
    }
    if (n < 2) {
        return 0;
    }
    if (n > SIZE_MAX / sizeof(*tmp)) {
        return -1;
    }

    bytes = n * sizeof(*tmp);

    tmp = malloc(bytes);
    if (tmp == NULL) {
        return -1;
    }

    passes = (sizeof(unsigned int) * CHAR_BIT + RADIX_BITS - 1u) / RADIX_BITS;
    src = arr;
    dst = tmp;

    for (pass = 0; pass < passes; ++pass) {
        size_t count[RADIX] = {0};
        unsigned int shift = (unsigned int)(pass * RADIX_BITS);
        size_t i;
        size_t sum;

        for (i = 0; i < n; ++i) {
            unsigned int key = (unsigned int)src[i] ^ SIGN_BIT;
            ++count[(key >> shift) & RADIX_MASK];
        }

        sum = 0;
        for (i = 0; i < RADIX; ++i) {
            size_t c = count[i];
            count[i] = sum;
            sum += c;
        }

        for (i = 0; i < n; ++i) {
            unsigned int key = (unsigned int)src[i] ^ SIGN_BIT;
            dst[count[(key >> shift) & RADIX_MASK]++] = src[i];
        }

        {
            int *swap = src;
            src = dst;
            dst = swap;
        }
    }

    if (src != arr) {
        size_t i;

        if (n > SIZE_MAX / sizeof(*arr)) {
            free(tmp);
            return -1;
        }

        for (i = 0; i < n; ++i) {
            arr[i] = src[i];
        }
    }

    free(tmp);
    return 0;
}

int main(void)
{
    int arr[] = {170, 45, 75, -90, 802, 24, 2, 66, -1, 0, INT_MAX, INT_MIN};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("Before: ");
    print_array(arr, n);

    if (radix_sort(arr, n) != 0) {
        fprintf(stderr, "radix_sort failed\n");
        return EXIT_FAILURE;
    }

    printf("After:  ");
    print_array(arr, n);

    return EXIT_SUCCESS;
}