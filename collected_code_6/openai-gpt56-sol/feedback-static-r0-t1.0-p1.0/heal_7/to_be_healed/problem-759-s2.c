#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *cursor;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    cursor = (const unsigned char *)text;

    if (*cursor == '+' || *cursor == '-') {
        ++cursor;
    }

    while (*cursor >= '0' && *cursor <= '9') {
        ++integer_digits;
        ++cursor;
    }

    if (integer_digits == 0 || *cursor != '.') {
        return false;
    }

    ++cursor;

    if (cursor[0] == '\0' ||
        cursor[0] < '0' || cursor[0] > '9') {
        return false;
    }

    ++cursor;

    if (cursor[0] == '\0' ||
        cursor[0] < '0' || cursor[0] > '9') {
        return false;
    }

    return cursor[1] == '\0';
}

static bool read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return false;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
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

        buffer[length++] = (char)(unsigned char)character;
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
    char *input = NULL;
    bool valid;

    if (!read_line(stdin, &input)) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    valid = is_decimal_with_precision_2(input);
    free(input);

    puts(valid ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}