#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    if (*p == '+' || *p == '-') {
        ++p;
    }

    while (*p >= '0' && *p <= '9') {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != '.') {
        return false;
    }

    ++p;

    return p[0] >= '0' && p[0] <= '9' &&
           p[1] >= '0' && p[1] <= '9' &&
           p[2] == '\0';
}

static bool read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            if (character == EOF && ferror(stdin)) {
                free(buffer);
                return false;
            }

            if (character == EOF && length == 0) {
                free(buffer);
                return false;
            }

            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

int main(void)
{
    char *input = NULL;

    if (!read_line(&input)) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");

    free(input);
    return EXIT_SUCCESS;
}