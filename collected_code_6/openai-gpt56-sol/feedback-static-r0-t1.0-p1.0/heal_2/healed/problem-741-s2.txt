#include <stdbool.h>
#include <stdio.h>

static bool all_characters_same(const char *string)
{
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    const char first = string[0];

    for (size_t i = 1U; string[i] != '\0'; ++i) {
        if (string[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }

        input[0] = '\0';
    } else {
        size_t length = 0U;

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
        } else if (!feof(stdin)) {
            int character;

            do {
                character = getchar();
            } while (character != '\n' && character != EOF);

            if (character == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }
    }

    puts(all_characters_same(input)
             ? "All characters are the same."
             : "Not all characters are the same.");

    return 0;
}