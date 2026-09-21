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
    char input[2];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    if (starts_with_vowel((unsigned char)input[0])) {
        puts("The string starts with a vowel.");
    } else {
        puts("The string does not start with a vowel.");
    }

    return 0;
}