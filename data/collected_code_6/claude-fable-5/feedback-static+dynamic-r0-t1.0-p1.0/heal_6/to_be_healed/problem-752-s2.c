#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#define INPUT_BUFFER_SIZE 64U

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

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1U] = '\0';

    len = strnlen(buffer, size);
    if (len > 0U && buffer[len - 1U] != '\n' && len == size - 1U) {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return -1;
    }

    return 0;
}

static int parse_unsigned(const char *buffer, unsigned int *out)
{
    char *endptr;
    long value;

    if (buffer == NULL || out == NULL) {
        return -1;
    }

    errno = 0;
    endptr = NULL;
    value = strtol(buffer, &endptr, 10);

    if (endptr == buffer) {
        return -1;
    }

    if (errno == ERANGE) {
        return -1;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }

    if (*endptr != '\0') {
        return -1;
    }

    if (value < 0L || (unsigned long)value > (unsigned long)UINT_MAX) {
        return -1;
    }

    *out = (unsigned int)value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    unsigned int n;
    unsigned long long answer;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter n: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error: failed to flush output\n");
        return EXIT_FAILURE;
    }

    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    if (parse_unsigned(buffer, &n) != 0) {
        fprintf(stderr, "Error: invalid input or out of range\n");
        return EXIT_FAILURE;
    }

    if (jacobsthal(n, &answer) != 0) {
        fprintf(stderr, "Error: result overflow or invalid argument\n");
        return EXIT_FAILURE;
    }

    printf("Jacobsthal(%u) = %llu\n", n, answer);

    return EXIT_SUCCESS;
}