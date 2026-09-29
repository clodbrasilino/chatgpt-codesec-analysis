#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 1;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 2; i <= n; ++i) {
        if (UINT64_MAX - current < previous) {
            return -1;
        }

        uint64_t next = current + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

static int read_input(size_t *value)
{
    unsigned long long input;
    int ch;
    int first;
    char terminator;

    if (value == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        first = getchar();
        if (first == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)first));

    if (ungetc(first, stdin) == EOF) {
        return -1;
    }

    errno = 0;
    if (scanf("%llu%c", &input, &terminator) != 2 || errno == ERANGE) {
        return -1;
    }

    if (!isspace((unsigned char)terminator)) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return -1;
        }
    }

    if (ferror(stdin)) {
        return -1;
    }

    if (input > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

int main(void)
{
    size_t input;
    uint64_t result;

    if (read_input(&input) != 0) {
        return EXIT_FAILURE;
    }

    if (count_tilings(input, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}