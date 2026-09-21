#include <stdbool.h>
#include <stdio.h>

static bool starts_with_vowel(int ch)
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
        return 1;
    }

    if (starts_with_vowel(ch)) {
        puts("The string starts with a vowel.");
    } else {
        puts("The string does not start with a vowel.");
    }

    return 0;
}