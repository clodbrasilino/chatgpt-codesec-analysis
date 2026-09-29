#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_word(const char *word, size_t length)
{
    if (word == NULL || length < 3U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!isalpha((unsigned char)word[i])) {
            return false;
        }
    }

    for (size_t i = 1U; i + 1U < length; ++i) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }

    return false;
}

static bool grow_buffer(char **buffer, size_t *capacity)
{
    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0U || *capacity > SIZE_MAX / 2U) {
        return false;
    }

    const size_t new_capacity = *capacity * 2U;
    char *new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return false;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return true;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    size_t capacity = 64U;
    size_t used = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return false;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used >= capacity - 1U) {
            if (!grow_buffer(&buffer, &capacity)) {
                free(buffer);
                return false;
            }
        }

        buffer[used] = (char)(unsigned char)ch;
        ++used;
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return true;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0U;

    if (!read_line(stdin, &word, &length)) {
        return EXIT_FAILURE;
    }

    const bool match = matches_word(word, length);
    free(word);

    if (puts(match ? "match" : "no match") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}