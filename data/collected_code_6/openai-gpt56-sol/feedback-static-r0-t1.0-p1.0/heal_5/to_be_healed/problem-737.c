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
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int first = getchar();

    if (first == EOF) {
        return 1;
    }

    if (starts_with_vowel((char[]){(char)first, '\0'})) {
        puts("The string starts with a vowel.");
    } else {
        puts("The string does not start with a vowel.");
    }

    return 0;
}