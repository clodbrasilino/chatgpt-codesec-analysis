#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;
    int ch = EOF;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return false;
    }

    if (*line == NULL || *capacity == 0U) {
        char *buffer;
        size_t initial_capacity = 128U;

        buffer = malloc(initial_capacity);
        if (buffer == NULL) {
            return false;
        }

        *line = buffer;
        *capacity = initial_capacity;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stream) == EOF) {
                    return false;
                }
            }
            break;
        }

        if (length >= *capacity - 1U) {
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

        (*line)[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream) != 0 || length == 0U) {
            return false;
        }
    }

    (*line)[length] = '\0';
    return true;
}

static bool matches_word_at_end(const char *text, size_t text_len,
                                const char *word, size_t word_len)
{
    size_t end;

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

    if (memcmp(text + end - word_len, word, word_len) != 0) {
        return false;
    }

    return end == word_len ||
           (isalnum((unsigned char)text[end - word_len - 1U]) == 0 &&
            text[end - word_len - 1U] != '_');
}

int main(void)
{
    char *text = NULL;
    char *word = NULL;
    size_t text_capacity = 0U;
    size_t word_capacity = 0U;
    size_t text_len;
    size_t word_len;
    int result = EXIT_FAILURE;

    if (!read_line(stdin, &text, &text_capacity)) {
        goto cleanup;
    }

    if (!read_line(stdin, &word, &word_capacity)) {
        goto cleanup;
    }

    text_len = strnlen(text, text_capacity);
    word_len = strnlen(word, word_capacity);

    if (text_len == text_capacity || word_len == word_capacity ||
        word_len == 0U) {
        goto cleanup;
    }

    puts(matches_word_at_end(text, text_len, word, word_len)
             ? "match"
             : "no match");

    result = EXIT_SUCCESS;

cleanup:
    free(word);
    free(text);
    return result;
}