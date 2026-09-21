#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

static int jacobsthal(unsigned int n, unsigned long long *result)
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

        if (prev > (ULLONG_MAX / 2ULL)) {
            return -1;
        }
        if (curr > ULLONG_MAX - (2ULL * prev)) {
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
    char buffer[64];
    char *endptr;
    unsigned long value;
    unsigned long long answer;

    printf("Enter n: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    if (buffer[0] == '-') {
        fprintf(stderr, "Error: n out of range\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    value = strtoul(buffer, &endptr, 10);

    if (endptr == buffer) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || value > (unsigned long)UINT_MAX) {
        fprintf(stderr, "Error: n out of range\n");
        return EXIT_FAILURE;
    }

    if (jacobsthal((unsigned int)value, &answer) != 0) {
        fprintf(stderr, "Error: result overflow or invalid argument\n");
        return EXIT_FAILURE;
    }

    printf("Jacobsthal(%lu) = %llu\n", value, answer);

    return EXIT_SUCCESS;
}