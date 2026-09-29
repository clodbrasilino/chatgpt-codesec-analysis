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

    if (*line == NULL || *capacity == 0U) {
        *capacity = 128U;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return false;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length + 1U >= *capacity) {
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

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        return false;
    }

    (*line)[length] = '\0';
    return true;
}

static bool matches_word_at_end(const char *text, const char *word)
{
    size_t text_len;
    size_t word_len;
    size_t end;

    if (text == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_len = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    word_len = strlen(word);
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
    int result = EXIT_FAILURE;

    if (!read_line(&text, &text_capacity)) {
        goto cleanup;
    }

    if (!read_line(&word, &word_capacity) || word[0] == '\0') {
        goto cleanup;
    }

    puts(matches_word_at_end(text, word) ? "match" : "no match");
    result = EXIT_SUCCESS;

cleanup:
    free(word);
    free(text);
    return result;
}