#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int first_repeated_character(const unsigned char *data, size_t length,
                             unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned int index = data[i];

        if (seen[index] != 0U) {
            *result = data[i];
            return 1;
        }

        seen[index] = 1U;
    }

    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 4096 };
    unsigned char *input = malloc((size_t)INPUT_CAPACITY);
    size_t length = 0;
    unsigned char repeated_character = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;
    int status;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length >= (size_t)INPUT_CAPACITY) {
            while (ch != EOF && ch != '\n') {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            }

            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }

            if (fputs("Input is too long.\n", stderr) == EOF) {
                free(input);
                return EXIT_FAILURE;
            }

            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    status = first_repeated_character(input, length, &repeated_character);

    if (status < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (status > 0) {
        if (putchar((int)repeated_character) == EOF ||
            putchar('\n') == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated character found.") == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(input);
    return EXIT_SUCCESS;
}