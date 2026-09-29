#include <stdbool.h>
#include <stdio.h>

static bool starts_with_vowel(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    switch (*str) {
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
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[2];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (starts_with_vowel(input)) {
        puts("The string starts with a vowel.");
    } else {
        puts("The string does not start with a vowel.");
    }

    return 0;
}