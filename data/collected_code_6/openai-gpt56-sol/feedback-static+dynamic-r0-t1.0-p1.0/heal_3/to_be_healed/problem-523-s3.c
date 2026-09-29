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
        unsigned char character = (unsigned char)string[i];

        if (isupper(character)) {
            has_upper = true;
        } else if (islower(character)) {
            has_lower = true;
        } else if (isdigit(character)) {
            has_digit = true;
        }
    }

    return has_upper && has_lower && has_digit;
}

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 64;
    size_t used = 0;
    char *buffer;

    if (line == NULL || length == NULL) {
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) || used == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (used >= SIZE_MAX - 1) {
            free(buffer);
            errno = EOVERFLOW;
            return false;
        }

        if (used == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                errno = EOVERFLOW;
                return false;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
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
    size_t line_length = 0;
    size_t required_length;

    if (printf("Required length: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&line, &line_length) ||
        !parse_size(line, &required_length)) {
        free(line);
        fprintf(stderr, "Invalid length.\n");
        return EXIT_FAILURE;
    }

    free(line);
    line = NULL;

    if (printf("String: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&line, &line_length)) {
        free(line);
        fprintf(stderr, "Failed to read the string.\n");
        return EXIT_FAILURE;
    }

    if (meets_requirements(line, line_length, required_length)) {
        puts("The string meets all requirements.");
        free(line);
        return EXIT_SUCCESS;
    }

    puts("The string does not meet all requirements.");
    free(line);
    return EXIT_FAILURE;
}