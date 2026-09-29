#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U

static char *replace_spaces(const char *source, size_t length, char replacement)
{
    char *result;
    size_t i;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        result[i] = source[i] == ' ' ? replacement : source[i];
    }

    result[length] = '\0';
    return result;
}

static int read_line(char **buffer, size_t *length)
{
    char *line;
    size_t capacity;
    size_t used;
    int ch;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    line = NULL;
    capacity = 0U;
    used = 0U;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (used >= INPUT_SIZE) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            free(line);
            return 0;
        }

        if (used + 1U >= capacity) {
            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(line);
                    return 0;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity > INPUT_SIZE + 1U) {
                new_capacity = INPUT_SIZE + 1U;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[used++] = (char)ch;
    }

    if (ch == EOF && used == 0U) {
        free(line);
        return 0;
    }

    if (line == NULL) {
        line = malloc(1U);
        if (line == NULL) {
            return 0;
        }
    }

    line[used] = '\0';
    *buffer = line;
    *length = used;
    return 1;
}

int main(void)
{
    char *input;
    char *replacement_line;
    char *result;
    size_t input_length;
    size_t replacement_length;
    char replacement;

    input = NULL;
    replacement_line = NULL;
    result = NULL;

    if (!read_line(&input, &input_length)) {
        fputs("Failed to read the string or input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(&replacement_line, &replacement_length)) {
        fputs("Failed to read the replacement character.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (replacement_length != 1U) {
        fputs("Invalid replacement character.\n", stderr);
        free(replacement_line);
        free(input);
        return EXIT_FAILURE;
    }

    replacement = replacement_line[0];
    free(replacement_line);

    result = replace_spaces(input, input_length, replacement);
    free(input);

    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}