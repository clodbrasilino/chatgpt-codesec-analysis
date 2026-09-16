#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool all_characters_same(const char *string)
{
    size_t i;

    if (string == NULL || string[0] == '\0') {
        return false;
    }

    for (i = 1U; string[i] != '\0'; ++i) {
        if (string[i] != string[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[length - 1U] = '\0';
    } else if (length == sizeof input - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character != '\n') {
            fputs("Input is too long.\n", stderr);
            return 1;
        }
    }

    puts(all_characters_same(input) ? "All characters are the same."
                                    : "Not all characters are the same.");

    return 0;
}