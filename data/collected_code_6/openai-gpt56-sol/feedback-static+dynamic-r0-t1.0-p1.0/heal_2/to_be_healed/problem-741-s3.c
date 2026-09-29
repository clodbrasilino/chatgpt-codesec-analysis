#include <stdbool.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 1024 };

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

            return 1;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (ch == EOF && length == 0) {
        fputs("No input provided.\n", stderr);
        return 1;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    input[length] = '\0';

    if (all_characters_same(input)) {
        puts("All characters are the same.");
    } else {
        puts("Not all characters are the same.");
    }

    return 0;
}