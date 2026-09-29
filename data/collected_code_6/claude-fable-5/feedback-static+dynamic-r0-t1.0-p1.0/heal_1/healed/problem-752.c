#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int jacobsthal(unsigned int n, unsigned long long *result)
{
    unsigned long long prev = 0ULL;
    unsigned long long curr = 1ULL;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = 0ULL;
        return 0;
    }

    if (n == 1U) {
        *result = 1ULL;
        return 0;
    }

    for (i = 2U; i <= n; i++) {
        unsigned long long next;

        if (prev > (ULLONG_MAX - curr) / 2ULL) {
            return -1;
        }
        next = curr + (2ULL * prev);
        prev = curr;
        curr = next;
    }

    *result = curr;
    return 0;
}

int main(void)
{
    unsigned int n;
    unsigned long long value;
    int scan_status;

    printf("Enter n: ");

    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (jacobsthal(n, &value) != 0) {
        fprintf(stderr, "Error: computation failed (overflow or invalid argument).\n");
        return EXIT_FAILURE;
    }

    printf("Jacobsthal(%u) = %llu\n", n, value);

    return EXIT_SUCCESS;
}