#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool meets_requirements(const char *string, size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    size_t length = 0;

    if (string == NULL) {
        return false;
    }

    while (string[length] != '\0') {
        unsigned char character = (unsigned char)string[length];

        if (isupper(character)) {
            has_upper = true;
        } else if (islower(character)) {
            has_lower = true;
        } else if (isdigit(character)) {
            has_digit = true;
        }

        ++length;
    }

    return length == required_length && has_upper && has_lower && has_digit;
}

static bool read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int character = EOF;

    if (line == NULL || capacity == NULL) {
        return false;
    }

    if (*line == NULL || *capacity == 0) {
        char *initial_line;
        size_t initial_capacity = 128;

        initial_line = malloc(initial_capacity);
        if (initial_line == NULL) {
            return false;
        }

        *line = initial_line;
        *capacity = initial_capacity;
    }

    for (;;) {
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            return false;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                return false;
            }

            new_capacity = *capacity * 2;
            if (new_capacity <= length + 1) {
                return false;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return false;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)character;
    }

    if (ferror(stdin)) {
        return false;
    }

    if (character == EOF && length == 0) {
        return false;
    }

    (*line)[length] = '\0';
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (unsigned long long)SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t required_length = 0;
    int result = EXIT_FAILURE;

    if (fputs("Required length: ", stdout) == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    if (!read_line(&line, &capacity) ||
        !parse_size(line, &required_length)) {
        fputs("Invalid length.\n", stderr);
        goto cleanup;
    }

    if (fputs("String: ", stdout) == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    if (!read_line(&line, &capacity)) {
        fputs("Failed to read the string.\n", stderr);
        goto cleanup;
    }

    if (meets_requirements(line, required_length)) {
        if (puts("The string meets all requirements.") == EOF) {
            goto cleanup;
        }
        result = EXIT_SUCCESS;
    } else {
        if (puts("The string does not meet all requirements.") == EOF) {
            goto cleanup;
        }
    }

cleanup:
    free(line);
    return result;
}