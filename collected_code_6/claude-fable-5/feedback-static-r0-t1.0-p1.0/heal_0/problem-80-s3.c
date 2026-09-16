#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int tetrahedral(unsigned int n, unsigned long long *result)
{
    unsigned long long a;
    unsigned long long b;
    unsigned long long c;
    unsigned long long product;

    if (result == NULL) {
        return -1;
    }

    a = (unsigned long long)n;
    b = (unsigned long long)n + 1ULL;
    c = (unsigned long long)n + 2ULL;

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return -1;
    }
    product = a * b;

    if (product != 0ULL && c > ULLONG_MAX / product) {
        return -1;
    }
    product = product * c;

    *result = product / 6ULL;
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long value = 0ULL;
    int scan_status;

    printf("Enter n: ");
    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (tetrahedral(n, &value) != 0) {
        fprintf(stderr, "Computation failed (overflow or invalid argument)\n");
        return EXIT_FAILURE;
    }

    printf("Tetrahedral number %u is %llu\n", n, value);
    return EXIT_SUCCESS;
}