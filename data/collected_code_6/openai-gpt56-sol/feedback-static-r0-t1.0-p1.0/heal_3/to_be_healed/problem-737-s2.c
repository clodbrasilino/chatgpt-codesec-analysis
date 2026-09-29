#include <stdbool.h>
#include <stdio.h>

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
    int first = getchar();

    if (first == EOF) {
        fputs(ferror(stdin) ? "Failed to read input.\n"
                           : "No input provided.\n",
              stderr);
        return 1;
    }

    int ch;
    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    puts(is_vowel(first) ? "Starts with a vowel"
                         : "Does not start with a vowel");

    return 0;
}