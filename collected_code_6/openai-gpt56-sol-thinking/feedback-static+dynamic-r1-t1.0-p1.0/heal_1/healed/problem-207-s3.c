#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool longest_repeating_subsequence_length(
    const char *text,
    size_t text_length,
    size_t *result)
{
    size_t *previous;
    size_t *current;

    if (text == NULL || result == NULL) {
        return false;
    }

    if (text_length == SIZE_MAX ||
        text_length + 1 > SIZE_MAX / sizeof(*previous)) {
        return false;
    }

    previous = calloc(text_length + 1, sizeof(*previous));
    current = calloc(text_length + 1, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return false;
    }

    for (size_t i = 1; i <= text_length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= text_length; ++j) {
            if (text[i - 1] == text[j - 1] && i != j) {
                current[j] = previous[j - 1] + 1;
            } else {
                current[j] = previous[j] > current[j - 1]
                                 ? previous[j]
                                 : current[j - 1];
            }
        }

        size_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    *result = previous[text_length];

    free(previous);
    free(current);
    return true;
}

static bool read_line(FILE *stream, char **line, size_t *line_length)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || line == NULL || line_length == NULL) {
        return false;
    }

    *line = NULL;
    *line_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_length = length;
    return true;
}

int main(void)
{
    char *text = NULL;
    size_t text_length = 0;
    size_t result = 0;
    bool output_failed;

    if (!read_line(stdin, &text, &text_length)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!longest_repeating_subsequence_length(
            text, text_length, &result)) {
        free(text);
        fputs("Failed to calculate the result.\n", stderr);
        return EXIT_FAILURE;
    }

    output_failed = printf("%zu\n", result) < 0;

    if (fflush(stdout) == EOF) {
        output_failed = true;
    }

    free(text);
    return output_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}