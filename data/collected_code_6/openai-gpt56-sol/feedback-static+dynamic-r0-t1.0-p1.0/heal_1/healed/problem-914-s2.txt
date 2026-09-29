#include <stdbool.h>
#include <stddef.h>
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
    char *line = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;

            if (new_capacity <= capacity ||
                new_capacity > SIZE_MAX / sizeof *line) {
                free(line);
                return NULL;
            }

            char *new_line = realloc(line, new_capacity * sizeof *line);
            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (ferror(stream) != 0) {
        free(line);
        return NULL;
    }

    if (character == EOF && length == 0U) {
        free(line);
        return NULL;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX / sizeof *line) {
            free(line);
            return NULL;
        }

        char *new_line = realloc(line, (capacity + 1U) * sizeof *line);
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

    const bool result = has_two_alternating_characters(input);
    free(input);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}