#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

enum { INPUT_SIZE = 1024 };

static int is_hexadecimal(const char *text, size_t length)
{
    size_t index = 0;

    if (text == NULL || length == 0) {
        return 0;
    }

    if (length >= 2 &&
        text[0] == '0' &&
        (text[1] == 'x' || text[1] == 'X')) {
        index = 2;
    }

    if (index == length) {
        return 0;
    }

    for (; index < length; ++index) {
        if (!isxdigit((unsigned char)text[index])) {
            return 0;
        }
    }

    return 1;
}

static int is_hex_even(const char *text, size_t length)
{
    unsigned char digit;

    if (text == NULL || length == 0) {
        return 0;
    }

    digit = (unsigned char)tolower((unsigned char)text[length - 1]);

    if (digit >= (unsigned char)'0' && digit <= (unsigned char)'9') {
        return ((digit - (unsigned char)'0') & 1U) == 0U;
    }

    return ((digit - (unsigned char)'a' + 10U) & 1U) == 0U;
}

static int line_is_complete(const char *buffer)
{
    size_t length = 0;

    while (length < INPUT_SIZE && buffer[length] != '\0') {
        ++length;
    }

    return length > 0 && buffer[length - 1] == '\n';
}

static size_t remove_line_ending(char *buffer)
{
    size_t length = 0;

    while (length < INPUT_SIZE && buffer[length] != '\0') {
        ++length;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        buffer[--length] = '\0';
    }

    return length;
}

static int discard_remaining_input(void)
{
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        if (line_is_complete(buffer)) {
            return 0;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("No input\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (!line_is_complete(input) && !feof(stdin)) {
        if (discard_remaining_input() != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Input too long\n", stderr);
        }
        return EXIT_FAILURE;
    }

    length = remove_line_ending(input);

    if (!is_hexadecimal(input, length)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_hex_even(input, length) ? "Even" : "Odd");
    return EXIT_SUCCESS;
}