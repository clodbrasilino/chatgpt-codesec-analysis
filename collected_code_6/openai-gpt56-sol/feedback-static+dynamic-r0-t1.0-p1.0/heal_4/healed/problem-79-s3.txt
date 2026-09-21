#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return (length % 2U) != 0U;
}

static int read_word(FILE *stream, char **word, size_t *length)
{
    size_t capacity = 16U;
    char *buffer = malloc(capacity);
    int character;

    if (buffer == NULL) {
        return -1;
    }

    *length = 0U;

    for (;;) {
        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || *length == 0U) {
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

        if (*length >= SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (*length + 1U >= capacity) {
            size_t new_capacity;
            char *resized_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized_buffer = realloc(buffer, new_capacity);
            if (resized_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized_buffer;
            capacity = new_capacity;
        }

        buffer[(*length)++] = (char)(unsigned char)character;
    }

    buffer[*length] = '\0';
    *word = buffer;
    return 0;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0U;

    if (read_word(stdin, &word, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (has_odd_length(length)) {
        puts("The word length is odd.");
    } else {
        puts("The word length is even.");
    }

    free(word);
    return EXIT_SUCCESS;
}