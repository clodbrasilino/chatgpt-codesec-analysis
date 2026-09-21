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

        if (isupper(ch)) {
            has_upper = true;
        } else if (islower(ch)) {
            has_lower = true;
        } else if (isdigit(ch)) {
            has_digit = true;
        }
    }

    return has_upper && has_lower && has_digit;
}

static bool discard_line(FILE *stream)
{
    char buffer[256];

    if (stream == NULL) {
        return false;
    }

    for (;;) {
        if (fgets(buffer, sizeof buffer, stream) == NULL) {
            return feof(stream) != 0 && ferror(stream) == 0;
        }

        for (size_t i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') {
                return true;
            }
        }
    }
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
        size_t available;
        char *result;
        size_t chunk_length;

        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return false;
        }

        available = capacity - used;
        if (available < 2U) {
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
            available = capacity - used;
        }

        result = fgets(buffer + used, (int)(available > (size_t)INT32_MAX
                                                ? INT32_MAX
                                                : available),
                      stream);

        if (result == NULL) {
            if (ferror(stream) != 0 || used == 0U) {
                free(buffer);
                return false;
            }
            break;
        }

        chunk_length = 0U;
        while (buffer[used + chunk_length] != '\0' &&
               buffer[used + chunk_length] != '\n') {
            ++chunk_length;
        }

        used += chunk_length;

        if (buffer[used] == '\n') {
            buffer[used] = '\0';
            break;
        }

        if (feof(stream) != 0) {
            break;
        }
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