#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_vowel(int ch)
{
    switch (ch) {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int ch = getchar();

    if (ch == EOF) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No input provided.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (ch == '\n') {
        fputs("No input provided.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_vowel(ch)
             ? "Starts with a vowel"
             : "Does not start with a vowel");

    return EXIT_SUCCESS;
}