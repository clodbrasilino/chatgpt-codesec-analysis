#include <stdbool.h>
#include <stdio.h>

static bool all_characters_same(const char *string)
{
    if (string == NULL || *string == '\0') {
        return false;
    }

    const char first = *string++;

    while (*string != '\0') {
        if (*string++ != first) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[1024];
    size_t length = 0U;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1U >= sizeof input) {
            while (character != '\n' && character != EOF) {
                character = getchar();
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    input[length] = '\0';

    puts(all_characters_same(input)
             ? "All characters are the same."
             : "Not all characters are the same.");

    return 0;
}