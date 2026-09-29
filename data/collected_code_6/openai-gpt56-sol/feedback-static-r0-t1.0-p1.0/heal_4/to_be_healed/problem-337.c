#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0U;
    int ch;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return false;
    }

    if (*line == NULL || *capacity < 2U) {
        char *buffer;
        size_t initial_capacity = 128U;

        buffer = realloc(*line, initial_capacity);
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
            } else if (next == EOF && ferror(stream) != 0) {
                return false;
            }

            break;
        }

        if (length == *capacity - 1U) {
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

    if (ch == EOF && (ferror(stream) != 0 || length == 0U)) {
        return false;
    }

    (*line)[length] = '\0';
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
    size_t text_len;
    size_t word_len;
    int result = EXIT_FAILURE;

    if (!read_line(stdin, &text, &text_capacity) ||
        !read_line(stdin, &word, &word_capacity)) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_len = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    word_len = strlen(word);

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