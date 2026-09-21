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

static bool read_line(FILE *stream, char **line, size_t *capacity,
                      size_t *length)
{
    size_t len = 0U;

    if (stream == NULL || line == NULL || capacity == NULL || length == NULL) {
        return false;
    }

    *length = 0U;

    if (!ensure_capacity(line, capacity, 2U)) {
        return false;
    }

    for (;;) {
        int ch = fgetc(stream);

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
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream) != 0) {
                    return false;
                }
            } else if (next != '\n') {
                if (ungetc(next, stream) == EOF) {
                    return false;
                }
            }

            break;
        }

        if (len > SIZE_MAX - 2U) {
            return false;
        }

        if (!ensure_capacity(line, capacity, len + 2U)) {
            return false;
        }

        (*line)[len] = (char)(unsigned char)ch;
        ++len;
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