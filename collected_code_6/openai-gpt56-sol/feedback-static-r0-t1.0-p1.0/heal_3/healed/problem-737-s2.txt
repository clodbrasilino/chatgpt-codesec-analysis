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
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Failed to read input.\n"
                           : "No input provided.\n",
              stderr);
        return 1;
    }

    if (input[0] == '\n' || input[0] == '\0') {
        fputs("No input provided.\n", stderr);
        return 1;
    }

    if (input[sizeof input - 2] != '\0' &&
        input[sizeof input - 2] != '\n') {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }
    }

    puts(is_vowel((unsigned char)input[0])
             ? "Starts with a vowel"
             : "Does not start with a vowel");

    return 0;
}