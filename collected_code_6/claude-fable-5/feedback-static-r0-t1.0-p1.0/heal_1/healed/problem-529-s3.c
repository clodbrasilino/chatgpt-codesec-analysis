#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

static int jacobsthal_lucas(unsigned int n, unsigned long long *result)
{
    unsigned long long prev;
    unsigned long long curr;
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
        unsigned long long next;

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

int main(int argc, char *const argv[])
{
    unsigned long parsed;
    unsigned long long value;
    char *endptr;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    parsed = strtoul(argv[1], &endptr, 10);

    if ((errno != 0) || (endptr == argv[1]) || (*endptr != '\0')) {
        (void)fprintf(stderr, "Invalid input: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (parsed > (unsigned long)UINT_MAX) {
        (void)fprintf(stderr, "Input too large: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (jacobsthal_lucas((unsigned int)parsed, &value) != 0) {
        (void)fprintf(stderr, "Overflow computing Jacobsthal-Lucas number for n = %lu\n", parsed);
        return EXIT_FAILURE;
    }

    if (printf("Jacobsthal-Lucas(%lu) = %llu\n", parsed, value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}