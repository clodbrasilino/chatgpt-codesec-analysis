#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_same(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    const char first = *str++;

    while (*str != '\0') {
        if (*str++ != first) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    enum { INPUT_CAPACITY = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= sizeof input) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    input[length] = '\0';

    puts(all_characters_same(input) ? "True" : "False");
    return EXIT_SUCCESS;
}