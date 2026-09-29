#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(FILE *stream, char **line, size_t *capacity,
                      size_t *length)
{
    int ch;

    if (stream == NULL || line == NULL || capacity == NULL ||
        length == NULL) {
        return false;
    }

    *length = 0;

    if (*line == NULL || *capacity < 2) {
        size_t initial_capacity = 128;
        char *buffer = realloc(*line, initial_capacity);

        if (buffer == NULL) {
            return false;
        }

        *line = buffer;
        *capacity = initial_capacity;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        size_t required;

        if (*length > SIZE_MAX - 2) {
            return false;
        }

        required = *length + 2;

        if (required > *capacity) {
            size_t new_capacity = *capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return false;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[*length] = (char)(unsigned char)ch;
        ++*length;
    }

    if (ferror(stream) != 0) {
        return false;
    }

    if (ch == EOF && *length == 0) {
        return false;
    }

    if (*length > 0 && (*line)[*length - 1] == '\r') {
        --*length;
    }

    (*line)[*length] = '\0';
    return true;
}

static bool matches_word_at_end(const char *text, size_t text_length,
                                const char *word, size_t word_length)
{
    size_t end;
    size_t start;

    if (text == NULL || word == NULL || word_length == 0) {
        return false;
    }

    end = text_length;

    while (end > 0 && isspace((unsigned char)text[end - 1]) != 0) {
        --end;
    }

    if (end > 0 && ispunct((unsigned char)text[end - 1]) != 0) {
        --end;
    }

    while (end > 0 && isspace((unsigned char)text[end - 1]) != 0) {
        --end;
    }

    if (word_length > end) {
        return false;
    }

    start = end - word_length;

    if (memcmp(text + start, word, word_length) != 0) {
        return false;
    }

    return start == 0 ||
           (isalnum((unsigned char)text[start - 1]) == 0 &&
            text[start - 1] != '_');
}

int main(void)
{
    char *text = NULL;
    char *word = NULL;
    size_t text_capacity = 0;
    size_t word_capacity = 0;
    size_t text_length = 0;
    size_t word_length = 0;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &text, &text_capacity, &text_length)) {
        goto cleanup;
    }

    if (!read_line(stdin, &word, &word_capacity, &word_length) ||
        word_length == 0) {
        goto cleanup;
    }

    puts(matches_word_at_end(text, text_length, word, word_length)
             ? "match"
             : "no match");

    status = EXIT_SUCCESS;

cleanup:
    free(word);
    free(text);
    return status;
}