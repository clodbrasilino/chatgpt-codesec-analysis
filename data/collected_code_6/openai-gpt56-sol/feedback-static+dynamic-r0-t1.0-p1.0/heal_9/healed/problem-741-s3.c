#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool all_characters_same(const char *str)
{
    if (str == NULL || str[0] == '\0') {
        return false;
    }

    for (size_t i = 1; str[i] != '\0'; ++i) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    } else {
        size_t length = strlen(input);

        if (length > 0 && input[length - 1] == '\n') {
            input[--length] = '\0';

            if (length > 0 && input[length - 1] == '\r') {
                input[--length] = '\0';
            }
        } else if (!feof(stdin)) {
            int ch;

            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        } else if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    }

    puts(all_characters_same(input) ? "True" : "False");
    return EXIT_SUCCESS;
}