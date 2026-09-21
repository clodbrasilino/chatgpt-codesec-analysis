#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    while (index < length) {
        if (!isxdigit((unsigned char)text[index])) {
            return 0;
        }
        ++index;
    }

    return 1;
}

static int is_hex_even(const char *text, size_t length)
{
    unsigned char digit;

    if (text == NULL || length == 0) {
        return 0;
    }

    digit = (unsigned char)text[length - 1];

    if (digit >= (unsigned char)'0' && digit <= (unsigned char)'9') {
        return ((digit - (unsigned char)'0') & 1U) == 0U;
    }

    digit = (unsigned char)tolower(digit);

    if (digit >= (unsigned char)'a' && digit <= (unsigned char)'f') {
        return ((digit - (unsigned char)'a' + 10U) & 1U) == 0U;
    }

    return 0;
}

static int discard_line(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }

    return character == EOF && ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char *input;
    size_t length;

    input = malloc(INPUT_SIZE);
    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_SIZE, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("No input\n", stderr);
        }
        free(input);
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length == INPUT_SIZE - 1U) {
        if (discard_line() != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Input too long\n", stderr);
        }
        free(input);
        return EXIT_FAILURE;
    }

    if (!is_hexadecimal(input, length)) {
        fputs("Invalid hexadecimal number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_hex_even(input, length) ? "Even" : "Odd");

    free(input);
    return EXIT_SUCCESS;
}