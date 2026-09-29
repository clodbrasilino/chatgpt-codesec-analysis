#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int last_element_parity(const int arr[], size_t n, size_t p, int *is_even)
{
    size_t i;
    unsigned int parity;

    if (arr == NULL || is_even == NULL || n == 0U || p >= n) {
        return -1;
    }

    parity = (arr[n - 1U] % 2 != 0) ? 1U : 0U;

    for (i = 0U; i < p; i++) {
        if (arr[i] % 2 != 0) {
            parity ^= 1U;
        }
    }

    *is_even = (parity == 0U) ? 1 : 0;
    return 0;
}

int main(void)
{
    int arr[] = { 7, 3, 5, 1, 2, 8 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t p = 3U;
    int is_even = 0;
    int status;

    status = last_element_parity(arr, n, p, &is_even);
    if (status != 0) {
        (void)fprintf(stderr, "Error: invalid input parameters\n");
        return EXIT_FAILURE;
    }

    if (is_even == 1) {
        (void)printf("Even\n");
    } else {
        (void)printf("Odd\n");
    }

    return EXIT_SUCCESS;
}