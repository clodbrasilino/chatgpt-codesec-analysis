#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

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

static bool discard_line(void)
{
    int ch;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n') {
            return true;
        }

        if (ch == '\r') {
            ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                ungetc(ch, stdin);
            }

            return ch != EOF || !ferror(stdin);
        }

        if (ch == EOF) {
            return !ferror(stdin);
        }
    }
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error.\n", stderr);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    } else {
        size_t length = strcspn(input, "\r\n");

        if (input[length] == '\0' && length > MAX_INPUT_LENGTH) {
            if (discard_line()) {
                fputs("Input is too long.\n", stderr);
            } else {
                fputs("Input error.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        input[length] = '\0';
    }

    puts(matches(input) ? "Match" : "No match");
    return EXIT_SUCCESS;
}