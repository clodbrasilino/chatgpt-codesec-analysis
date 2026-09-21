#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_digit(unsigned char ch)
{
    return ch >= (unsigned char)'0' && ch <= (unsigned char)'9';
}

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == (unsigned char)'+' || *p == (unsigned char)'-') {
        ++p;
    }

    while (is_digit(*p)) {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != (unsigned char)'.') {
        return false;
    }

    ++p;

    if (!is_digit(p[0]) || !is_digit(p[1])) {
        return false;
    }

    return p[2] == '\0';
}

static bool read_line(char **line)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return false;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
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

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        return false;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return false;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

int main(void)
{
    char *input;

    if (!read_line(&input)) {
        return ferror(stdin) ? 1 : 0;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    free(input);

    return 0;
}