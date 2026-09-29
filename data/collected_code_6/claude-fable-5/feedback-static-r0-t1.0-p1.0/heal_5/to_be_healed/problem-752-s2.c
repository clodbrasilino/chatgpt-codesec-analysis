#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
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
    int ch;
    const char *terminator;

    if (buffer == NULL || size == 0U || size > (size_t)INT_MAX) {
        return -1;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1U] = '\0';

    terminator = memchr(buffer, '\0', size);
    if (terminator == NULL) {
        return -1;
    }

    len = (size_t)(terminator - buffer);

    if (len == 0U) {
        return -1;
    }

    if (buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    char *endptr;
    const char *p;
    unsigned long value;
    unsigned long long answer;

    printf("Enter n: ");

    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    p = buffer;
    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '\0') {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (*p == '-') {
        fprintf(stderr, "Error: n out of range\n");
        return EXIT_FAILURE;
    }

    if (!isdigit((unsigned char)*p) && *p != '+') {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    value = strtoul(p, &endptr, 10);

    if (endptr == NULL || endptr == p) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
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