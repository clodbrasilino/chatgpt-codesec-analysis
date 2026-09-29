#include <ctype.h>
#include <errno.h>
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
        unsigned char ch = (unsigned char)string[i];

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

static bool read_line(char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 64;
    size_t used = 0;

    if (line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return false;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used > SIZE_MAX - 2) {
            free(buffer);
            return false;
        }

        if (used + 1 >= capacity) {
            size_t required = used + 2;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return false;
            }

            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)ch;
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
    const unsigned char *cursor;
    char *end;
    unsigned long long parsed;

    if (text == NULL || value == NULL) {
        return false;
    }

    cursor = (const unsigned char *)text;
    while (*cursor != '\0' && isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-' || *cursor == '+') {
        return false;
    }

    errno = 0;
    parsed = strtoull((const char *)cursor, &end, 10);

    if (errno == ERANGE || end == (const char *)cursor) {
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

int main(void)
{
    char *line = NULL;
    size_t line_length = 0;
    size_t required_length = 0;

    if (fputs("Enter the required length: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&line, &line_length) ||
        !parse_size(line, &required_length)) {
        free(line);
        fputs("Invalid length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);
    line = NULL;
    line_length = 0;

    if (fputs("Enter the string: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&line, &line_length)) {
        free(line);
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    const char *message =
        meets_requirements(line, line_length, required_length)
            ? "The string meets all requirements.\n"
            : "The string does not meet all requirements.\n";

    if (fputs(message, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}