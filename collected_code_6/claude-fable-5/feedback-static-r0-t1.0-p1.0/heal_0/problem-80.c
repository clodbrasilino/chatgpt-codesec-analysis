#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int tetrahedral(unsigned int n, unsigned long long *result)
{
    unsigned long long a;
    unsigned long long b;
    unsigned long long c;

    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = 0ULL;
        return 0;
    }

    a = (unsigned long long)n;
    b = a + 1ULL;
    c = a + 2ULL;

    if (a > ULLONG_MAX / b) {
        return -1;
    }

    if ((a * b) > ULLONG_MAX / c) {
        return -1;
    }

    *result = (a * b * c) / 6ULL;
    return 0;
}

int main(void)
{
    unsigned int n;
    unsigned long long result;
    int scan_status;

    printf("Enter n: ");

    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (tetrahedral(n, &result) != 0) {
        fprintf(stderr, "Computation failed: value out of range\n");
        return EXIT_FAILURE;
    }

    printf("Tetrahedral number %u is %llu\n", n, result);

    return EXIT_SUCCESS;
}