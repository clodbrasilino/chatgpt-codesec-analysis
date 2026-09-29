#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int has_odd_length(size_t length)
{
    return (length & (size_t)1) != 0;
}

int main(void)
{
    size_t length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    return EXIT_FAILURE;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                return EXIT_FAILURE;
            }

            break;
        }

        if (length == SIZE_MAX) {
            return EXIT_FAILURE;
        }

        ++length;
    }

    if (puts(has_odd_length(length) ? "Odd" : "Even") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}