#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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

static int hexadecimal_is_even(
    const char *text,
    size_t length,
    bool *is_even)
{
    size_t cursor = 0;
    int last_value = -1;

    if (text == NULL || is_even == NULL) {
        return -1;
    }

    while (cursor < length &&
           isspace((unsigned char)text[cursor]) != 0) {
        cursor++;
    }

    if (cursor + 1 < length &&
        text[cursor] == '0' &&
        (text[cursor + 1] == 'x' || text[cursor + 1] == 'X')) {
        cursor += 2;
    }

    while (cursor < length) {
        int value = hex_digit_value((unsigned char)text[cursor]);

        if (value < 0) {
            break;
        }

        last_value = value;
        cursor++;
    }

    if (last_value < 0) {
        return -1;
    }

    while (cursor < length &&
           isspace((unsigned char)text[cursor]) != 0) {
        cursor++;
    }

    if (cursor != length) {
        return -1;
    }

    *is_even = (last_value % 2) == 0;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length;
    ssize_t count;
    bool is_even;

    count = getline(&input, &capacity, stdin);

    if (count < 0 || ferror(stdin) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    length = (size_t)count;

    if (memchr(input, '\0', length) != NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        length--;
    }

    if (hexadecimal_is_even(input, length, &is_even) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (is_even) {
        puts("Even");
    } else {
        puts("Odd");
    }

    return EXIT_SUCCESS;
}