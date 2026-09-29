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

    first = getchar();
    if (first == EOF) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No input provided.\n", stderr);
        }
        return 1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    char input[2] = {(char)first, '\0'};
    puts(starts_with_vowel(input) ? "Starts with a vowel"
                                 : "Does not start with a vowel");

    return 0;
}