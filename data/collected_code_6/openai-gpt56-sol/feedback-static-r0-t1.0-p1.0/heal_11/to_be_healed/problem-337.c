#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool ensure_capacity(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL) {
        return false;
    }

    if (required <= *capacity) {
        return *buffer != NULL;
    }

    new_capacity = (*capacity < 128U) ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity < required) {
        return false;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return false;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return true;
}

static bool append_character(char **buffer, size_t *capacity, size_t *length,
                             unsigned char character)
{
    if (buffer == NULL || capacity == NULL || length == NULL ||
        *length > SIZE_MAX - 2U) {
        return false;
    }

    if (!ensure_capacity(buffer, capacity, *length + 2U)) {
        return false;
    }

    (*buffer)[*length] = (char)character;
    ++(*length);
    (*buffer)[*length] = '\0';

    return true;
}

static bool read_line(FILE *stream, char **line, size_t *capacity,
                      size_t *length)
{
    size_t len = 0U;
    int ch;

    if (stream == NULL || line == NULL || capacity == NULL || length == NULL) {
        return false;
    }

    *length = 0U;

    if (!ensure_capacity(line, capacity, 2U)) {
        return false;
    }

    (*line)[0] = '\0';

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

            if (next == EOF) {
                if (ferror(stream) != 0) {
                    return false;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                return false;
            }

            break;
        }

        if (!append_character(line, capacity, &len, (unsigned char)ch)) {
            return false;
        }
    }

    if (ch == EOF && (ferror(stream) != 0 || len == 0U)) {
        return false;
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
    size_t text_length = 0U;
    size_t word_length = 0U;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &text, &text_capacity, &text_length)) {
        goto cleanup;
    }

    if (!read_line(stdin, &word, &word_capacity, &word_length) ||
        word_length == 0U) {
        goto cleanup;
    }

    if (puts(matches_word_at_end(text, text_length, word, word_length)
                 ? "match"
                 : "no match") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(word);
    free(text);
    return status;
}