#include <ctype.h>
#include <stdbool.h>
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

static bool read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 64U;
    size_t used = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    int ch;
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (used + 1U >= capacity) {
            if (capacity > (size_t)-1 / 2U) {
                free(buffer);
                return false;
            }

            size_t new_capacity = capacity * 2U;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return false;
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

    puts(matches_word(word, length) ? "match" : "no match");
    free(word);

    return EXIT_SUCCESS;
}