#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t max_uppercase_run(FILE *stream, int *error)
{
    size_t maximum = 0;
    size_t current = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (error != NULL) {
        *error = 0;
    }

    if (stream == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                if (error != NULL) {
                    *error = 1;
                }
                return 0;
            }
            break;
        }

        if (isupper((unsigned char)ch) != 0) {
            if (current == SIZE_MAX) {
                if (error != NULL) {
                    *error = 1;
                }
                return 0;
            }

            ++current;

            if (current > maximum) {
                maximum = current;
            }
        } else {
            current = 0;
        }
    }

    return maximum;
}

int main(void)
{
    int error = 0;
    size_t maximum = max_uppercase_run(stdin, &error);

    if (error != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}