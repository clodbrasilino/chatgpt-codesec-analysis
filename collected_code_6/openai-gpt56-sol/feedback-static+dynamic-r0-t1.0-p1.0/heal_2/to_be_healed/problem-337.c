#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return false;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return false;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length + 1 >= *capacity) {
            if (*capacity > SIZE_MAX / 2) {
                return false;
            }

            new_capacity = *capacity * 2;
            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return false;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        return false;
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    (*line)[length] = '\0';
    return true;
}

static bool matches_word_at_end(const char *text, size_t text_len,
                                const char *word, size_t word_len)
{
    size_t end;
    size_t start;

    if (text == NULL || word == NULL || word_len == 0) {
        return false;
    }

    end = text_len;

    while (end > 0 && isspace((unsigned char)text[end - 1]) != 0) {
        --end;
    }

    if (end > 0 && ispunct((unsigned char)text[end - 1]) != 0) {
        --end;
    }

    while (end > 0 && isspace((unsigned char)text[end - 1]) != 0) {
        --end;
    }

    if (word_len > end) {
        return false;
    }

    start = end - word_len;

    if (memcmp(text + start, word, word_len) != 0) {
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
    size_t text_len;
    size_t word_len;
    int status = EXIT_FAILURE;

    if (!read_line(&text, &text_capacity) ||
        !read_line(&word, &word_capacity)) {
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

    if (word_len == 0) {
        goto cleanup;
    }

    puts(matches_word_at_end(text, text_len, word, word_len)
             ? "match"
             : "no match");

    status = EXIT_SUCCESS;

cleanup:
    free(word);
    free(text);
    return status;
}