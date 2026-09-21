#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096U

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    while (*p >= (unsigned char)'0' && *p <= (unsigned char)'9') {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != (unsigned char)'.') {
        return false;
    }

    ++p;

    if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
        return false;
    }
    ++p;

    if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
        return false;
    }
    ++p;

    return *p == (unsigned char)'\0';
}

static bool read_line(char *buffer, size_t capacity)
{
    size_t length = 0;
    int character;

    if (buffer == NULL || capacity < 2) {
        return false;
    }

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            while ((character = getchar()) != '\n' && character != EOF) {
            }
            buffer[0] = '\0';
            return false;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';

    if (character == EOF && (ferror(stdin) || length == 0)) {
        return false;
    }

    return true;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(input, INPUT_SIZE)) {
        fputs("Input error\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");

    free(input);
    return EXIT_SUCCESS;
}