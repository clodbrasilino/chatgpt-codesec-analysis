#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decagonal_number(uint64_t n, uint64_t *result)
{
    uint64_t factor;

    if (result == NULL || n == 0 || n > UINT64_MAX / UINT64_C(4)) {
        return 0;
    }

    factor = UINT64_C(4) * n - UINT64_C(3);

    if (n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t value;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0') {
            ++length;
        }

        if (length == sizeof input) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (length == 0) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (input[length - 1] != '\n' && !feof(stdin)) {
            int ch;

            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!decagonal_number((uint64_t)value, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}