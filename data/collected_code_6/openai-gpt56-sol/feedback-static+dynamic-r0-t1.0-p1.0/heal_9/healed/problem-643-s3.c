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

static int grow_buffer(char **buffer, size_t *capacity)
{
    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0U || *capacity > SIZE_MAX / 2U) {
        return -1;
    }

    size_t new_capacity = *capacity * 2U;
    char *new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int append_character(char **buffer, size_t *capacity, size_t *used,
                            unsigned char ch)
{
    if (buffer == NULL || capacity == NULL || used == NULL ||
        *buffer == NULL || *capacity == 0U || *used >= *capacity) {
        return -1;
    }

    if (*used >= *capacity - 1U) {
        if (grow_buffer(buffer, capacity) != 0) {
            return -1;
        }
    }

    (*buffer)[*used] = (char)ch;
    ++(*used);
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    const size_t initial_capacity = 128U;
    size_t capacity = initial_capacity;
    size_t used = 0U;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (append_character(&buffer, &capacity, &used,
                             (unsigned char)ch) != 0) {
            free(buffer);
            return -1;
        }
    }

    if (used == 0U && feof(stream)) {
        free(buffer);
        return 0;
    }

    if (used >= capacity) {
        free(buffer);
        return -1;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0U;
    int status = read_line(stdin, &word, &length);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (fputs(matches_word(word, length) ? "match\n" : "no match\n",
              stdout) == EOF) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}