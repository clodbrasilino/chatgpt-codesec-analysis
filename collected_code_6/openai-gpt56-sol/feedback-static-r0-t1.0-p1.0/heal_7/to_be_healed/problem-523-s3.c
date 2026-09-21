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

    while (length < required_length && string[length] != '\0') {
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

    return length == required_length &&
           string[length] == '\0' &&
           has_upper &&
           has_lower &&
           has_digit;
}

static bool read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return false;
    }

    if (*line == NULL || *capacity < 2) {
        char *new_line;
        size_t initial_capacity = 128;

        new_line = malloc(initial_capacity);
        if (new_line == NULL) {
            return false;
        }

        free(*line);
        *line = new_line;
        *capacity = initial_capacity;
    }

    for (;;) {
        int character;

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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        (*line)[length++] = (char)(unsigned char)character;
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    (*line)[length] = '\0';
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    char *end;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || isspace((unsigned char)text[0])) {
        return false;
    }

    errno = 0;
    end = NULL;
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
    size_t required_length;
    int result = EXIT_FAILURE;

    if (fputs("Required length: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        goto cleanup;
    }

    if (!read_line(stdin, &line, &capacity) ||
        !parse_size(line, &required_length)) {
        fputs("Invalid length.\n", stderr);
        goto cleanup;
    }

    if (fputs("String: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        goto cleanup;
    }

    if (!read_line(stdin, &line, &capacity)) {
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