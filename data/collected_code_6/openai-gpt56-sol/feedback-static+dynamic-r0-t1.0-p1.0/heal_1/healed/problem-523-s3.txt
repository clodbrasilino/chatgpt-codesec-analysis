#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
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

    for (size_t i = 0U; i < length; ++i) {
        const unsigned char character = (unsigned char)string[i];

        if (isupper(character) != 0) {
            has_upper = true;
        } else if (islower(character) != 0) {
            has_lower = true;
        } else if (isdigit(character) != 0) {
            has_digit = true;
        }
    }

    return has_upper && has_lower && has_digit;
}

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 64U;
    size_t used = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            if (character == EOF && ferror(stdin)) {
                free(buffer);
                return false;
            }

            if (character == EOF && used == 0U) {
                free(buffer);
                return false;
            }

            break;
        }

        if (used == SIZE_MAX - 1U) {
            free(buffer);
            errno = EOVERFLOW;
            return false;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            char *new_buffer = realloc(buffer, new_capacity);

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

    if (text == NULL || *text == '\0' || *text == '-') {
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
    size_t line_length = 0U;
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