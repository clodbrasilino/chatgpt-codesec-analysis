#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL || length == 0) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin])) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1])) {
        --end;
    }

    if (end - begin >= 2 &&
        hex[begin] == '0' &&
        (hex[begin + 1] == 'x' || hex[begin + 1] == 'X')) {
        begin += 2;
    }

    if (begin == end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (!isxdigit((unsigned char)hex[i])) {
            return 0;
        }
    }

    last = (unsigned char)tolower((unsigned char)hex[end - 1]);
    *is_even = last == '0' || last == '2' || last == '4' ||
               last == '6' || last == '8' || last == 'a' ||
               last == 'c' || last == 'e';

    return 1;
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 2];
    size_t length;
    int even;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Invalid hexadecimal number.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(stdin);
            }

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (!is_hex_even(input, length, &even)) {
        fputs("Invalid hexadecimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(even ? "Even" : "Odd");
    return EXIT_SUCCESS;
}