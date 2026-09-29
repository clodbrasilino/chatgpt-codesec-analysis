#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_odd_bits(uint32_t value)
{
    return value | UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *start;
    char *end;
    uintmax_t parsed;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", set_odd_bits((uint32_t)parsed));
    return EXIT_SUCCESS;
}