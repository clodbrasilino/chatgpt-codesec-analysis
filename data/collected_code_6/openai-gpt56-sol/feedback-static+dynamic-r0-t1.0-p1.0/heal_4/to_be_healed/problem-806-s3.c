#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t max_uppercase_run(const char *str)
{
    size_t maximum = 0;
    size_t current = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str) != 0) {
            ++current;
            if (current > maximum) {
                maximum = current;
            }
        } else {
            current = 0;
        }

        ++str;
    }

    return maximum;
}

int main(void)
{
    size_t maximum = 0;
    size_t current = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        if (isupper((unsigned char)ch) != 0) {
            ++current;
            if (current > maximum) {
                maximum = current;
            }
        } else {
            current = 0;
        }
    }

    if (printf("%zu\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}