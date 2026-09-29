#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool string_length(const char *text, size_t *length)
{
    size_t count = 0;

    if (text == NULL || length == NULL) {
        return false;
    }

    while (text[count] != '\0') {
        if (count == SIZE_MAX - 1) {
            return false;
        }

        ++count;
    }

    *length = count;
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
        unsigned char character;
        size_t bytes_read = fread(&character, sizeof(character), 1, stream);

        if (bytes_read == 0) {
            if (ferror(stream)) {
                free(buffer);
                return false;
            }

            if (!feof(stream)) {
                free(buffer);
                return false;
            }

            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\0') {
            free(buffer);
            return false;
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

        buffer[length++] = (char)character;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_length = length;

    return true;
}

static bool longest_repeating_subsequence_length(
    const char *text,
    size_t length,
    size_t *result)
{
    size_t element_count;
    size_t *dp;

    if (text == NULL || result == NULL) {
        return false;
    }

    *result = 0;

    if (length == SIZE_MAX) {
        return false;
    }

    element_count = length + 1;

    if (element_count > SIZE_MAX / sizeof(*dp)) {
        return false;
    }

    dp = calloc(element_count, sizeof(*dp));
    if (dp == NULL) {
        return false;
    }

    for (size_t i = 1; i <= length; ++i) {
        size_t diagonal = 0;

        for (size_t j = 1; j <= length; ++j) {
            size_t previous = dp[j];
            size_t best = dp[j] > dp[j - 1] ? dp[j] : dp[j - 1];

            if (i != j && text[i - 1] == text[j - 1]) {
                if (diagonal == SIZE_MAX) {
                    free(dp);
                    return false;
                }

                size_t candidate = diagonal + 1;

                if (candidate > best) {
                    best = candidate;
                }
            }

            dp[j] = best;
            diagonal = previous;
        }
    }

    *result = dp[length];
    free(dp);
    return true;
}

int main(int argc, char *argv[])
{
    const char *text;
    char *allocated_text = NULL;
    size_t text_length;
    size_t result;

    if (argc == 2) {
        text = argv[1];

        if (!string_length(text, &text_length)) {
            fprintf(stderr, "Invalid input string.\n");
            return EXIT_FAILURE;
        }
    } else if (argc == 1) {
        if (!read_line(stdin, &allocated_text, &text_length)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }

        text = allocated_text;
    } else {
        fprintf(stderr, "Usage: %s [string]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!longest_repeating_subsequence_length(text, text_length, &result)) {
        free(allocated_text);
        fprintf(stderr, "Failed to calculate the result.\n");
        return EXIT_FAILURE;
    }

    free(allocated_text);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}