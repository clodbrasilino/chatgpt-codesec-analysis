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

    if (string == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)string[i];

        has_upper = has_upper || isupper(ch) != 0;
        has_lower = has_lower || islower(ch) != 0;
        has_digit = has_digit || isdigit(ch) != 0;
    }

    return length == required_length && has_upper && has_lower && has_digit;
}

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 64;
    size_t used = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                free(buffer);
                return false;
            }
            break;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
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

        buffer[used++] = (char)ch;
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

    if (errno == ERANGE || end == text) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
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

    if (printf("Enter the required length: ") < 0 || fflush(stdout) == EOF) {
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

    if (printf("Enter the string: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&line, &line_length)) {
        fprintf(stderr, "Failed to read the string.\n");
        return EXIT_FAILURE;
    }

    if (meets_requirements(line, line_length, required_length)) {
        if (printf("The string meets all requirements.\n") < 0) {
            free(line);
            return EXIT_FAILURE;
        }
    } else {
        if (printf("The string does not meet all requirements.\n") < 0) {
            free(line);
            return EXIT_FAILURE;
        }
    }

    free(line);
    return EXIT_SUCCESS;
}