#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static bool has_two_alternating_characters(const char *string)
{
    if (string == NULL || string[0] == '\0' || string[1] == '\0') {
        return false;
    }

    const char first = string[0];
    const char second = string[1];

    if (first == second) {
        return false;
    }

    for (size_t i = 2U; string[i] != '\0'; ++i) {
        const char expected = (i % 2U == 0U) ? first : second;

        if (string[i] != expected) {
            return false;
        }
    }

    return true;
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    size_t capacity = 128U;
    size_t length = 0U;
    char *line = malloc(capacity);

    if (line == NULL) {
        return NULL;
    }

    line[0] = '\0';

    for (;;) {
        size_t available = capacity - length;

        if (available < 2U) {
            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return NULL;
            }

            const size_t new_capacity = capacity * 2U;

            if (new_capacity > (size_t)INT_MAX) {
                free(line);
                return NULL;
            }

            char *new_line = realloc(line, new_capacity);

            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
            capacity = new_capacity;
            available = capacity - length;
        }

        if (fgets(line + length, (int)available, stream) == NULL) {
            if (ferror(stream) != 0 || length == 0U) {
                free(line);
                return NULL;
            }

            line[length] = '\0';
            return line;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        const size_t added = strlen(line + length);
        length += added;

        if (length > 0U && line[length - 1U] == '\n') {
            line[--length] = '\0';

            if (length > 0U && line[length - 1U] == '\r') {
                line[--length] = '\0';
            }

            return line;
        }

        if (feof(stream) != 0) {
            return line;
        }
    }
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    const bool result = has_two_alternating_characters(input);
    free(input);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}