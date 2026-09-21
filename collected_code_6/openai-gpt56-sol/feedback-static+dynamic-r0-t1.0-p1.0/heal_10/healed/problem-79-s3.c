#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return (length & (size_t)1) != 0;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *temporary;

    if (buffer == NULL || *buffer == NULL || capacity == NULL ||
        *capacity == 0 || *capacity > SIZE_MAX / 2) {
        return -1;
    }

    new_capacity = *capacity * 2;
    temporary = realloc(*buffer, new_capacity);
    if (temporary == NULL) {
        return -1;
    }

    *buffer = temporary;
    *capacity = new_capacity;
    return 0;
}

static int read_word(FILE *stream, char **word, size_t *length)
{
    size_t capacity = 16;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || word == NULL || length == NULL) {
        return -1;
    }

    *word = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next_character = fgetc(stream);

            if (next_character == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return -1;
                }
            } else if (next_character != '\n') {
                if (ungetc(next_character, stream) == EOF) {
                    free(buffer);
                    return -1;
                }
            }

            break;
        }

        if (used >= capacity - 1) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return -1;
            }
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    buffer[used] = '\0';
    *word = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0;
    int status = EXIT_SUCCESS;

    if (read_word(stdin, &word, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(has_odd_length(length)
                 ? "The word length is odd."
                 : "The word length is even.") == EOF) {
        status = EXIT_FAILURE;
    }

    free(word);
    return status;
}