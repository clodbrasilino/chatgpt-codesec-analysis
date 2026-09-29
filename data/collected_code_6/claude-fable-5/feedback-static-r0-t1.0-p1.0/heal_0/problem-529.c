#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int jacobsthal_lucas(unsigned int n, unsigned long long *result)
{
    unsigned long long prev;
    unsigned long long curr;
    unsigned long long next;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = 2ULL;
        return 0;
    }

    if (n == 1U) {
        *result = 1ULL;
        return 0;
    }

    prev = 2ULL;
    curr = 1ULL;

    for (i = 2U; i <= n; i++) {
        if (prev > (ULLONG_MAX / 2ULL)) {
            return -1;
        }
        if (curr > (ULLONG_MAX - (2ULL * prev))) {
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
    int rc;

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    rc = jacobsthal_lucas(n, &value);
    if (rc != 0) {
        fprintf(stderr, "Computation failed: overflow or invalid argument\n");
        return EXIT_FAILURE;
    }

    if (printf("Jacobsthal-Lucas(%u) = %llu\n", n, value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}