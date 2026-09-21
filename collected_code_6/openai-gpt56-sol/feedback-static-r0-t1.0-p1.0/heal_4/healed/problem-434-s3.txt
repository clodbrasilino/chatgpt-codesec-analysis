#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool matches(const char *str)
{
    if (str == NULL || str[0] != 'a' || str[1] != 'b') {
        return false;
    }

    str += 2;

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char input[MAX_INPUT_LENGTH + 1];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error.\n", stderr);
            return EXIT_FAILURE;
        }
        input[0] = '\0';
    } else {
        size_t length = 0;

        while (input[length] != '\0' &&
               input[length] != '\n' &&
               input[length] != '\r') {
            ++length;
        }

        if (input[length] == '\0' && length == MAX_INPUT_LENGTH) {
            int ch = fgetc(stdin);

            if (ch != EOF && ch != '\n' && ch != '\r') {
                while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
                }

                if (ferror(stdin)) {
                    fputs("Input error.\n", stderr);
                } else {
                    fputs("Input is too long.\n", stderr);
                }

                return EXIT_FAILURE;
            }

            if (ferror(stdin)) {
                fputs("Input error.\n", stderr);
                return EXIT_FAILURE;
            }
        }

        input[length] = '\0';
    }

    puts(matches(input) ? "Match" : "No match");
    return EXIT_SUCCESS;
}