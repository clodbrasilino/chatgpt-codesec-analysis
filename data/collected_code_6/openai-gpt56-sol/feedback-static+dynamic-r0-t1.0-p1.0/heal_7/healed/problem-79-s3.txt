#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return (length % 2U) != 0U;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *resized_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (*capacity > SIZE_MAX / 2U) {
        return -1;
    }

    new_capacity = *capacity * 2U;
    resized_buffer = realloc(*buffer, new_capacity);
    if (resized_buffer == NULL) {
        return -1;
    }

    *buffer = resized_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_word(FILE *stream, char **word, size_t *length)
{
    size_t capacity = 16U;
    size_t used = 0U;
    char *buffer;

    if (stream == NULL || word == NULL || length == NULL) {
        return -1;
    }

    *word = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0U) {
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
            } else if (next_character != '\n' &&
                       ungetc(next_character, stream) == EOF) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (used >= capacity - 1U) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return -1;
            }
        }

        buffer[used] = (char)(unsigned char)character;
        ++used;
    }

    buffer[used] = '\0';
    *word = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0U;

    if (read_word(stdin, &word, &length) != 0) {
        return EXIT_FAILURE;
    }

    puts(has_odd_length(length)
             ? "The word length is odd."
             : "The word length is even.");

    free(word);
    return EXIT_SUCCESS;
}