#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    long value;
    unsigned long long answer;
    size_t len;

    printf("Enter n: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0U && buffer[len - 1U] != '\n' && len == sizeof(buffer) - 1U) {
        fprintf(stderr, "Error: input too long\n");
        return EXIT_FAILURE;
    }

    endptr = NULL;
    value = strtol(buffer, &endptr, 10);

    if (endptr == buffer) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (value < 0L || (unsigned long)value > (unsigned long)UINT_MAX) {
        fprintf(stderr, "Error: n out of range\n");
        return EXIT_FAILURE;
    }

    if (jacobsthal((unsigned int)value, &answer) != 0) {
        fprintf(stderr, "Error: result overflow or invalid argument\n");
        return EXIT_FAILURE;
    }

    printf("Jacobsthal(%ld) = %llu\n", value, answer);

    return EXIT_SUCCESS;
}