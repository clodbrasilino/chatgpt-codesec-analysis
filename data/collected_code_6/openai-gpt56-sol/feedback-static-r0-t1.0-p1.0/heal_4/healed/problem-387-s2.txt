#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0U;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL || length == 0U) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin]) != 0) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1U]) != 0) {
        --end;
    }

    if (begin == end) {
        return 0;
    }

    if (end - begin >= 2U &&
        hex[begin] == '0' &&
        (hex[begin + 1U] == 'x' || hex[begin + 1U] == 'X')) {
        begin += 2U;
    }

    if (begin == end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (isxdigit((unsigned char)hex[i]) == 0) {
            return 0;
        }
    }

    last = (unsigned char)tolower((unsigned char)hex[end - 1U]);
    *is_even = last == '0' || last == '2' || last == '4' ||
               last == '6' || last == '8' || last == 'a' ||
               last == 'c' || last == 'e';

    return 1;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char input[MAX_INPUT_LENGTH + 1U];
    size_t length = 0U;
    int ch;
    int even;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= MAX_INPUT_LENGTH) {
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(stdin);
            }

            if (ch == EOF && ferror(stdin) != 0) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (is_hex_even(input, length, &even) == 0) {
        fputs("Invalid hexadecimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(even != 0 ? "Even" : "Odd");
    return EXIT_SUCCESS;
}