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

        if (has_upper && has_lower && has_digit) {
            return true;
        }
    }

    return false;
}

static bool grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0 || required <= *capacity) {
        return false;
    }

    new_capacity = *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return false;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return false;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return true;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 64;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int input = fgetc(stream);

        if (input == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return false;
            }
            break;
        }

        if (input == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (used + 1 >= capacity) {
            if (!grow_buffer(&buffer, &capacity, used + 2)) {
                free(buffer);
                return false;
            }
        }

        buffer[used++] = (char)(unsigned char)input;
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

    if (*cursor == '\0' || *cursor == '+' || *cursor == '-') {
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
    size_t required_length;
    const char *message;

    if (fputs("Enter the required length: ", stdout) == EOF ||
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

    if (fputs("Enter the string: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, &line, &line_length)) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    message = meets_requirements(line, line_length, required_length)
                  ? "The string meets all requirements.\n"
                  : "The string does not meet all requirements.\n";

    if (fputs(message, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}