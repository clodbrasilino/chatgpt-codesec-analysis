#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool meets_requirements(const char *string, size_t length,
                               size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    if (string == NULL || length != required_length) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (isupper(character)) {
            has_upper = true;
        } else if (islower(character)) {
            has_lower = true;
        } else if (isdigit(character)) {
            has_digit = true;
        }

        if (has_upper && has_lower && has_digit) {
            return true;
        }
    }

    return false;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 64;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        errno = EINVAL;
        return false;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int character;

        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                errno = EOVERFLOW;
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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || isspace((unsigned char)text[0])) {
        return false;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

int main(void)
{
    char *line = NULL;
    size_t line_length = 0;
    size_t required_length;
    bool valid;

    if (fputs("Required length: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, &line, &line_length) ||
        !parse_size(line, &required_length)) {
        free(line);
        fputs("Invalid length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);
    line = NULL;

    if (fputs("String: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, &line, &line_length)) {
        free(line);
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    valid = meets_requirements(line, line_length, required_length);
    free(line);

    if (valid) {
        if (puts("The string meets all requirements.") == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (puts("The string does not meet all requirements.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}