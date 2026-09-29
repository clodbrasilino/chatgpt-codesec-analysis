#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int hex_digit_value(unsigned char character)
{
    if (character >= '0' && character <= '9') {
        return character - '0';
    }

    if (character >= 'a' && character <= 'f') {
        return character - 'a' + 10;
    }

    if (character >= 'A' && character <= 'F') {
        return character - 'A' + 10;
    }

    return -1;
}

static int hexadecimal_is_even(const char *text, bool *is_even)
{
    const unsigned char *cursor;
    int last_value = -1;

    if (text == NULL || is_even == NULL) {
        return -1;
    }

    cursor = (const unsigned char *)text;

    while (isspace(*cursor) != 0) {
        cursor++;
    }

    if (cursor[0] == '0' && (cursor[1] == 'x' || cursor[1] == 'X')) {
        cursor += 2;
    }

    while (*cursor != '\0') {
        int value = hex_digit_value(*cursor);

        if (value < 0) {
            break;
        }

        last_value = value;
        cursor++;
    }

    if (last_value < 0) {
        return -1;
    }

    while (isspace(*cursor) != 0) {
        cursor++;
    }

    if (*cursor != '\0') {
        return -1;
    }

    *is_even = (last_value % 2) == 0;
    return 0;
}

int main(void)
{
    char input[1024];
    char *newline;
    bool is_even;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else {
        int next_character = fgetc(stdin);

        if (next_character != '\n' && next_character != EOF) {
            do {
                next_character = fgetc(stdin);
            } while (next_character != '\n' && next_character != EOF);

            return EXIT_FAILURE;
        }

        if (next_character == EOF && ferror(stdin) != 0) {
            return EXIT_FAILURE;
        }
    }

    if (hexadecimal_is_even(input, &is_even) != 0) {
        return EXIT_FAILURE;
    }

    puts(is_even ? "Even" : "Odd");

    return EXIT_SUCCESS;
}