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

static int read_line(char **line, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    free(buffer);
                    return -1;
                }
            } else if (next == EOF && ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (used == capacity - 1U) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2U;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (used == 0U && feof(stdin)) {
        free(buffer);
        return 0;
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
    int status = read_line(&word, &length);

    if (status < 0) {
        return 1;
    }

    if (status == 0) {
        return 0;
    }

    int result = printf("%s\n",
                        matches_word(word, length) ? "match" : "no match");

    free(word);

    if (result < 0) {
        return 1;
    }

    return 0;
}