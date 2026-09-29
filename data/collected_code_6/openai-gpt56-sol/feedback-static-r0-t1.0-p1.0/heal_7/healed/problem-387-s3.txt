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

static int consume_line_remainder(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) == 0;
}

int main(void)
{
    char *input;
    size_t length;
    int is_even;

    input = malloc(INPUT_CAPACITY + 2U);
    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)(INPUT_CAPACITY + 2U), stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid hexadecimal number\n", stderr);
        }
        free(input);
        return EXIT_FAILURE;
    }

    length = 0U;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > INPUT_CAPACITY) {
        if (!consume_line_remainder()) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid hexadecimal number\n", stderr);
        }
        free(input);
        return EXIT_FAILURE;
    } else if (ferror(stdin) != 0) {
        fputs("Input error\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    is_even = 0;
    if (!is_hex_even(input, length, &is_even)) {
        fputs("Invalid hexadecimal number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_even ? "Even" : "Odd");
    free(input);
    return EXIT_SUCCESS;
}