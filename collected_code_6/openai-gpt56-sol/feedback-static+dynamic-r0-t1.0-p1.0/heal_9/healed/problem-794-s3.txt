#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum { INPUT_SIZE = 1024 };

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

static int discard_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    if (ferror(stdin)) {
        perror("fgetc");
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }

        puts("No match");
        return 0;
    }

    size_t length = 0U;

    while (length < sizeof input &&
           input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] == '\r') {
        input[length] = '\0';

        if (length + 1U < sizeof input && input[length + 1U] == '\n') {
            input[length + 1U] = '\0';
        } else if (discard_line() != 0) {
            return 1;
        }
    } else {
        int ch;

        if (length > INPUT_SIZE) {
            if (discard_line() != 0) {
                return 1;
            }

            fputs("Input exceeds maximum length\n", stderr);
            return 1;
        }

        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (discard_line() != 0) {
                return 1;
            }

            fputs("Input exceeds maximum length\n", stderr);
            return 1;
        }

        if (ferror(stdin)) {
            perror("fgetc");
            return 1;
        }
    }

    if (length > INPUT_SIZE) {
        fputs("Input exceeds maximum length\n", stderr);
        return 1;
    }

    input[length] = '\0';
    puts(matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}