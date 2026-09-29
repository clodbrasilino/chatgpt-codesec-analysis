#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

    for (;;) {
        int character;

        if (length == capacity - 1U) {
            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return NULL;
            }

            const size_t new_capacity = capacity * 2U;
            char *new_line = realloc(line, new_capacity);

            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) != 0 || length == 0U) {
                free(line);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        line[length++] = (char)character;
    }

    line[length] = '\0';
    return line;
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