#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int tetrahedral_number(unsigned int n, unsigned long long *result)
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

    if (n > 2642244U) {
        return -1;
    }

    a = (unsigned long long)n;
    b = (unsigned long long)n + 1ULL;
    c = (unsigned long long)n + 2ULL;

    if (a % 2ULL == 0ULL) {
        a /= 2ULL;
    } else {
        b /= 2ULL;
    }

    if (a % 3ULL == 0ULL) {
        a /= 3ULL;
    } else if (b % 3ULL == 0ULL) {
        b /= 3ULL;
    } else {
        c /= 3ULL;
    }

    *result = a * b * c;
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

    if (tetrahedral_number(n, &result) != 0) {
        fprintf(stderr, "Value out of range\n");
        return EXIT_FAILURE;
    }

    printf("Tetrahedral number %u is %llu\n", n, result);

    return EXIT_SUCCESS;
}