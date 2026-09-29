#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(FILE *stream, char **line, size_t *capacity,
                      size_t *length)
{
    size_t len = 0U;
    /* Possible weaknesses found:
     *  Variable 'ch' is assigned a value that is never used. [unreadVariable]
     */
    int ch = EOF;

    if (stream == NULL || line == NULL || capacity == NULL ||
        length == NULL) {
        return false;
    }

    if (*line == NULL || *capacity < 2U) {
        size_t initial_capacity = 128U;
        char *buffer;

        if (*line == NULL) {
            buffer = malloc(initial_capacity);
        } else {
            buffer = realloc(*line, initial_capacity);
        }

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
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0 || len == 0U) {
                return false;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream) != 0) {
                    return false;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                return false;
            }

            break;
        }

        if (len >= *capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (*capacity > SIZE_MAX / 2U) {
                return false;
            }

            new_capacity = *capacity * 2U;
            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return false;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[len++] = (char)(unsigned char)ch;
    }

    (*line)[len] = '\0';
    *length = len;
    return true;
}

static bool matches_word_at_end(const char *text, size_t text_len,
                                const char *word, size_t word_len)
{
    size_t end;
    size_t start;

    if (text == NULL || word == NULL || word_len == 0U) {
        return false;
    }

    end = text_len;

    while (end > 0U && isspace((unsigned char)text[end - 1U]) != 0) {
        --end;
    }

    if (end > 0U && ispunct((unsigned char)text[end - 1U]) != 0) {
        --end;
    }

    while (end > 0U && isspace((unsigned char)text[end - 1U]) != 0) {
        --end;
    }

    if (word_len > end) {
        return false;
    }

    start = end - word_len;

    if (memcmp(text + start, word, word_len) != 0) {
        return false;
    }

    return start == 0U ||
           (isalnum((unsigned char)text[start - 1U]) == 0 &&
            text[start - 1U] != '_');
}

int main(void)
{
    char *text = NULL;
    char *word = NULL;
    size_t text_capacity = 0U;
    size_t word_capacity = 0U;
    size_t text_len = 0U;
    size_t word_len = 0U;
    int result = EXIT_FAILURE;

    if (!read_line(stdin, &text, &text_capacity, &text_len) ||
        !read_line(stdin, &word, &word_capacity, &word_len)) {
        goto cleanup;
    }

    if (word_len == 0U) {
        goto cleanup;
    }

    if (puts(matches_word_at_end(text, text_len, word, word_len)
                 ? "match"
                 : "no match") == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(word);
    free(text);
    return result;
}