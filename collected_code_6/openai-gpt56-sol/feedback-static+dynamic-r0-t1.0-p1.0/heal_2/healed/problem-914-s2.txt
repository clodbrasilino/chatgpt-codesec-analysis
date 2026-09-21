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

    char *line = NULL;
    size_t length = 0U;
    size_t capacity = 0U;

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF || character == '\n') {
            if (character == EOF && (ferror(stream) != 0 || length == 0U)) {
                free(line);
                return NULL;
            }
            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(line);
                    return NULL;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity > SIZE_MAX - 1U) {
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
        }

        line[length++] = (char)character;
    }

    if (length == SIZE_MAX) {
        free(line);
        return NULL;
    }

    if (capacity <= length) {
        char *new_line = realloc(line, length + 1U);
        if (new_line == NULL) {
            free(line);
            return NULL;
        }
        line = new_line;
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

    bool result = has_two_alternating_characters(input);
    free(input);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}