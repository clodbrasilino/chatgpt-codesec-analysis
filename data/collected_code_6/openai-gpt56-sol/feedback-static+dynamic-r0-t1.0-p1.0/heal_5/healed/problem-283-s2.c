#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int frequencies_are_valid(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)input;
         *p != '\0';
         ++p) {
        if (!isdigit(*p)) {
            return 0;
        }

        size_t digit = (size_t)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return 0;
        }

        ++frequencies[digit];
    }

    return 1;
}

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 2];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }

        puts("false");
        return EXIT_SUCCESS;
    }

    size_t length = 0;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        if (discard_line() != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Input too long\n", stderr);
        }

        return EXIT_FAILURE;
    } else if (length == MAX_INPUT_LENGTH) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            if (discard_line() != 0) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input too long\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    puts(frequencies_are_valid(input) ? "true" : "false");
    return EXIT_SUCCESS;
}