#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return false;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return false;
            }

            break;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= used + 1) {
                free(buffer);
                return false;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

static bool contains_word(const char *sentence, size_t sentence_length,
                          const char *word, size_t word_length)
{
    if (sentence == NULL || word == NULL || word_length == 0 ||
        word_length > sentence_length) {
        return false;
    }

    for (size_t i = 0; i <= sentence_length - word_length; ++i) {
        bool left_boundary;
        bool right_boundary;

        if (memcmp(sentence + i, word, word_length) != 0) {
            continue;
        }

        left_boundary =
            i == 0 || !is_word_character((unsigned char)sentence[i - 1]);

        right_boundary =
            i + word_length == sentence_length ||
            !is_word_character((unsigned char)sentence[i + word_length]);

        if (left_boundary && right_boundary) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char *sentence = NULL;
    char *word = NULL;
    size_t sentence_length = 0;
    size_t word_length = 0;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &sentence, &sentence_length)) {
        goto cleanup;
    }

    if (!read_line(stdin, &word, &word_length) || word_length == 0) {
        goto cleanup;
    }

    if (puts(contains_word(sentence, sentence_length, word, word_length)
                 ? "Word is present."
                 : "Word is not present.") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(word);
    free(sentence);
    return status;
}