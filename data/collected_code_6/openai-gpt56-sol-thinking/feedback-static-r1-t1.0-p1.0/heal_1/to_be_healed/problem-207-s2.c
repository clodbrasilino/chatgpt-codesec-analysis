#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int character;

    if (stream == NULL || line == NULL) {
        return false;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n' && character != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (character == '\0') {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
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

    if (ferror(stream)) {
        free(buffer);
        return false;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

static bool longest_repeating_subsequence_length(const char *text, size_t *result)
{
    size_t length;
    size_t *dp;
    size_t i;
    size_t j;

    if (text == NULL || result == NULL) {
        return false;
    }

    *result = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(text);

    if (length > SIZE_MAX / sizeof(*dp) - 1) {
        return false;
    }

    dp = calloc(length + 1, sizeof(*dp));
    if (dp == NULL) {
        return false;
    }

    for (i = 1; i <= length; ++i) {
        size_t diagonal = 0;

        for (j = 1; j <= length; ++j) {
            size_t previous = dp[j];
            size_t best = dp[j] > dp[j - 1] ? dp[j] : dp[j - 1];

            if (i != j && text[i - 1] == text[j - 1]) {
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
    size_t result;

    if (argc == 2) {
        text = argv[1];
    } else if (argc == 1) {
        if (!read_line(stdin, &allocated_text)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }
        text = allocated_text;
    } else {
        fprintf(stderr, "Usage: %s [string]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!longest_repeating_subsequence_length(text, &result)) {
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