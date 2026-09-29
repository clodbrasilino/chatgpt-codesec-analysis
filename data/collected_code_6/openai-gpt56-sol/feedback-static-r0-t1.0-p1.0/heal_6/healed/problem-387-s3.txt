#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0U;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL) {
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

    last = (unsigned char)hex[end - 1U];

    if (last >= (unsigned char)'0' && last <= (unsigned char)'9') {
        *is_even = ((unsigned int)(last - (unsigned char)'0') & 1U) == 0U;
    } else {
        *is_even = last == (unsigned char)'A' ||
                   last == (unsigned char)'C' ||
                   last == (unsigned char)'E' ||
                   last == (unsigned char)'a' ||
                   last == (unsigned char)'c' ||
                   last == (unsigned char)'e';
    }

    return 1;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) == 0;
}

int main(void)
{
    char input[INPUT_CAPACITY + 1U];
    size_t length;
    int is_even;

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid hexadecimal number\n", stderr);
        }
        return EXIT_FAILURE;
    }

    length = 0U;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            if (!discard_line()) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Invalid hexadecimal number\n", stderr);
            }
            return EXIT_FAILURE;
        }

        if (ferror(stdin) != 0) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    is_even = 0;
    if (!is_hex_even(input, length, &is_even)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_even ? "Even" : "Odd");
    return EXIT_SUCCESS;
}