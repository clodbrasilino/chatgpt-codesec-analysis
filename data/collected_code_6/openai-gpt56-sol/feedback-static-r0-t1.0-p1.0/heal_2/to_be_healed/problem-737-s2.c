#include <stdbool.h>
#include <stdio.h>

static bool starts_with_vowel(const char *string)
{
    if (string == NULL) {
        return false;
    }

    switch (string[0]) {
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
    int first;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    first = getchar();
    if (first == EOF) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No input provided.\n", stderr);
        }
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  Variable 'input' can be declared as const array [constVariable]
     */
    char input[2] = {(char)first, '\0'};
    puts(starts_with_vowel(input) ? "Starts with a vowel"
                                 : "Does not start with a vowel");

    return 0;
}