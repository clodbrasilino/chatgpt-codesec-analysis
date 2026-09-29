#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(char **line, size_t *capacity, size_t *length)
{
    int ch;

    if (line == NULL || capacity == NULL || length == NULL) {
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

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (*length > SIZE_MAX - 2) {
            return false;
        }

        if (*length + 1 >= *capacity) {
            size_t required = *length + 2;
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

        (*line)[(*length)++] = (char)(unsigned char)ch;
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

    if (!read_line(&text, &text_capacity, &text_length)) {
        goto cleanup;
    }

    if (!read_line(&word, &word_capacity, &word_length) ||
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