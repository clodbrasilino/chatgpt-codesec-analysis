#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool meets_requirements(const char *text, size_t length,
                               size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    if (text == NULL || length != required_length) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)text[i];

        has_upper = has_upper || isupper(ch) != 0;
        has_lower = has_lower || islower(ch) != 0;
        has_digit = has_digit || isdigit(ch) != 0;
    }

    return has_upper && has_lower && has_digit;
}

static bool discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return false;
    }

    while ((ch = fgetc(stream)) != '\n') {
        if (ch == EOF) {
            return false;
        }
    }

    return true;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 64U;
    size_t used = 0U;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || used == 0U) {
                free(buffer);
                return false;
            }
            break;
        }

        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return false;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

int main(void)
{
    size_t required_length;
    size_t input_length;
    char *input = NULL;

    if (scanf("%zu", &required_length) != 1) {
        return EXIT_FAILURE;
    }

    if (!discard_line(stdin)) {
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, &input, &input_length)) {
        return EXIT_FAILURE;
    }

    puts(meets_requirements(input, input_length, required_length)
             ? "Valid"
             : "Invalid");

    free(input);
    return EXIT_SUCCESS;
}