#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned long long gcd_ull(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        unsigned long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static int lcm_array(const unsigned long long *arr, size_t n, unsigned long long *result)
{
    size_t i;
    unsigned long long lcm;

    if (arr == NULL || result == NULL || n == 0U) {
        return -1;
    }

    lcm = arr[0];
    if (lcm == 0ULL) {
        return -1;
    }

    for (i = 1U; i < n; i++) {
        unsigned long long g;
        unsigned long long factor;

        if (arr[i] == 0ULL) {
            return -1;
        }

        g = gcd_ull(lcm, arr[i]);
        factor = arr[i] / g;

        if (factor != 0ULL && lcm > ULLONG_MAX / factor) {
            return -1;
        }

        lcm = lcm * factor;
    }

    *result = lcm;
    return 0;
}

int main(void)
{
    unsigned long long numbers[] = {4ULL, 6ULL, 8ULL, 12ULL};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    unsigned long long result = 0ULL;

    if (lcm_array(numbers, count, &result) != 0) {
        if (fprintf(stderr, "Error: could not compute LCM\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("LCM = %llu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}