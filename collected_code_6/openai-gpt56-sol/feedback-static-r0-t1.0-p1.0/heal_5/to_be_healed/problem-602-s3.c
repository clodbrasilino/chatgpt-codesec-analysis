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

    for (size_t i = 0U; i < length; ++i) {
        unsigned char character = data[i];

        if (seen[character] != 0U) {
            *result = character;
            return 1;
        }

        seen[character] = 1U;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[4096];
    size_t length = 0U;
    int ch;

    while (length < sizeof input &&
           /* Possible weaknesses found:
            * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
            */
           (ch = getchar()) != EOF &&
           ch != '\n') {
        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (length == sizeof input && ch != EOF && ch != '\n') {
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != EOF && ch != '\n');

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    unsigned char repeated_character;
    int status = first_repeated_character(input, length, &repeated_character);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status > 0) {
        if (putchar((int)repeated_character) == EOF ||
            putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character found.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}