#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int pell_number(unsigned int n, unsigned long long *result)
{
    unsigned long long previous;
    unsigned long long current;
    unsigned long long next;
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

    previous = 0ULL;
    current = 1ULL;

    for (i = 2U; i <= n; i++) {
        if (current > (ULLONG_MAX - previous) / 2ULL) {
            return -1;
        }
        next = (2ULL * current) + previous;
        previous = current;
        current = next;
    }

    *result = current;
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
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (pell_number(n, &result) != 0) {
        fprintf(stderr, "Error: computation failed or overflow for n = %u\n", n);
        return EXIT_FAILURE;
    }

    printf("Pell number P(%u) = %llu\n", n, result);

    return EXIT_SUCCESS;
}