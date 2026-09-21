#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static bool is_lowercase_letter(char c)
{
    return c >= 'a' && c <= 'z';
}

static bool is_matching_sequence(const char *text, size_t length)
{
    if (text == NULL || length == 0U) {
        return false;
    }

    if (!is_lowercase_letter(text[0]) ||
        !is_lowercase_letter(text[length - 1U])) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!is_lowercase_letter(text[i]) && text[i] != '_') {
            return false;
        }

        if (text[i] == '_' &&
            (i == 0U ||
             i + 1U >= length ||
             text[i - 1U] == '_' ||
             text[i + 1U] == '_')) {
            return false;
        }
    }

    return true;
}

static int find_sequences(const char *text)
{
    size_t i = 0U;
    int count = 0;

    if (text == NULL) {
        return -1;
    }

    while (text[i] != '\0') {
        while (text[i] != '\0' &&
               !is_lowercase_letter(text[i]) &&
               text[i] != '_') {
            ++i;
        }

        const size_t start = i;

        while (text[i] != '\0' &&
               (is_lowercase_letter(text[i]) || text[i] == '_')) {
            ++i;
        }

        if (i > start && is_matching_sequence(text + start, i - start)) {
            if (fwrite(text + start, 1U, i - start, stdout) != i - start ||
                fputc('\n', stdout) == EOF) {
                return -1;
            }

            if (count == INT_MAX) {
                return -1;
            }

            ++count;
        }
    }

    return count;
}

static bool append_character(char **line, size_t *length, size_t *capacity,
                             char character)
{
    if (*length == SIZE_MAX - 1U) {
        return false;
    }

    const size_t required = *length + 2U;

    if (required > *capacity) {
        size_t new_capacity = *capacity == 0U ? 128U : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2U) {
                new_capacity = required;
                break;
            }

            new_capacity *= 2U;
        }

        char *new_line = realloc(*line, new_capacity);
        if (new_line == NULL) {
            return false;
        }

        *line = new_line;
        *capacity = new_capacity;
    }

    (*line)[(*length)++] = character;
    return true;
}

static bool process_line(char **line, size_t *length, size_t *capacity)
{
    if (*line == NULL) {
        *line = malloc(1U);
        if (*line == NULL) {
            return false;
        }

        *capacity = 1U;
    }

    (*line)[*length] = '\0';

    if (find_sequences(*line) < 0) {
        return false;
    }

    *length = 0U;
    return true;
}

int main(void)
{
    char *line = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int result = EXIT_SUCCESS;
    int input_character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((input_character = fgetc(stdin)) != EOF) {
        if (input_character == '\n') {
            if (!process_line(&line, &length, &capacity)) {
                result = EXIT_FAILURE;
                goto cleanup;
            }
        } else if (!append_character(&line, &length, &capacity,
                                     (char)input_character)) {
            result = EXIT_FAILURE;
            goto cleanup;
        }
    }

    if (ferror(stdin)) {
        result = EXIT_FAILURE;
        goto cleanup;
    }

    if (length > 0U && !process_line(&line, &length, &capacity)) {
        result = EXIT_FAILURE;
    }

cleanup:
    free(line);
    return result;
}