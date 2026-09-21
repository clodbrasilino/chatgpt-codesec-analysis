#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024U

static char *replace_spaces(const char *source, size_t source_size,
                            char replacement)
{
    const char *terminator;
    char *result;
    size_t length;
    size_t i;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
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

static int read_line(char **line, size_t *length)
{
    char *buffer;
    size_t capacity;
    size_t used;
    int ch;

    if (line == NULL || length == NULL) {
        return 0;
    }

    capacity = 128U;
    used = 0U;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return 0;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && used == 0U) {
        free(buffer);
        return 0;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input;
    char *replacement_line;
    char replacement;
    char *result;
    size_t input_length;
    size_t replacement_length;

    if (!read_line(&input, &input_length)) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input_length >= INPUT_SIZE) {
        fputs("Input string is too long.\n", stderr);
        free(input);
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

    result = replace_spaces(input, input_length + 1U, replacement);
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