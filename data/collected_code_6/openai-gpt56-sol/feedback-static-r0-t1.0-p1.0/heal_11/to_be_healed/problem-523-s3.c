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

static bool grow_buffer(char **buffer, size_t *capacity, size_t minimum)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || minimum == 0) {
        return false;
    }

    new_capacity = *capacity;

    if (new_capacity < 128) {
        new_capacity = 128;
    }

    while (new_capacity < minimum) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = minimum;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < minimum) {
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

static bool read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;
    int character;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return false;
    }

    if (*line == NULL || *capacity < 2) {
        if (!grow_buffer(line, capacity, 2)) {
            return false;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            return false;
        }

        if (length + 1 >= *capacity) {
            if (!grow_buffer(line, capacity, length + 2)) {
                return false;
            }
        }

        (*line)[length++] = (char)character;
    }

    if (ferror(stream) || (character == EOF && length == 0)) {
        return false;
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    (*line)[length] = '\0';
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || isspace((unsigned char)text[0])) {
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