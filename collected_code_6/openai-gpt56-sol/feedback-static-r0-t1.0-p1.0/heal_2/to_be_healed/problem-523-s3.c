#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
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

    for (; string[length] != '\0'; ++length) {
        unsigned char character = (unsigned char)string[length];

        if (isupper(character)) {
            has_upper = true;
        } else if (islower(character)) {
            has_lower = true;
        } else if (isdigit(character)) {
            has_digit = true;
        }
    }

    return length == required_length && has_upper && has_lower && has_digit;
}

static bool read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int character;

    if (line == NULL || capacity == NULL) {
        return false;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return false;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= *capacity) {
            size_t new_capacity;

            if (*capacity > SIZE_MAX / 2) {
                return false;
            }

            new_capacity = *capacity * 2;
            char *new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return false;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        return false;
    }

    (*line)[length] = '\0';
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    char *end;
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
    size_t required_length;
    int result = 1;

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
        puts("The string meets all requirements.");
        result = 0;
    } else {
        puts("The string does not meet all requirements.");
    }

cleanup:
    free(line);
    return result;
}