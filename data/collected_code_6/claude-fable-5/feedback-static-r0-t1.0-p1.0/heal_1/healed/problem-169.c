#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int pell(unsigned int n, unsigned long long *result)
{
    unsigned long long prev;
    unsigned long long curr;
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

    prev = 0ULL;
    curr = 1ULL;

    for (i = 2U; i <= n; i++) {
        unsigned long long next;

        if (curr > (ULLONG_MAX - prev) / 2ULL) {
            return -1;
        }
        next = (2ULL * curr) + prev;
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

    if (pell(n, &value) != 0) {
        fprintf(stderr, "Error: computation failed or overflow occurred.\n");
        return EXIT_FAILURE;
    }

    printf("Pell(%u) = %llu\n", n, value);

    return EXIT_SUCCESS;
}