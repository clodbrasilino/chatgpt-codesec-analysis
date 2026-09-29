#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int has_odd_parity(unsigned long long value)
{
    int parity = 0;

    while (value != 0ULL) {
        parity ^= 1;
        value &= value - 1ULL;
    }

    return parity;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    char *newline;
    unsigned long long value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return EXIT_FAILURE;
        }
    }

    if (input[0] == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(input, &end, 0);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               has_odd_parity(value) ? "Odd parity" : "Even parity") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}