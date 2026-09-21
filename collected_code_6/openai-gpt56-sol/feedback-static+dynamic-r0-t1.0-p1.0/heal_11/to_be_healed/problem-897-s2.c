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

static bool contains_word(const char *sentence, size_t sentence_length,
                          const char *word, size_t word_length)
{
    if (sentence == NULL || word == NULL || word_length == 0 ||
        word_length > sentence_length) {
        return false;
    }

    size_t last_start = sentence_length - word_length;

    for (size_t i = 0; i <= last_start; ++i) {
        if (memcmp(sentence + i, word, word_length) != 0) {
            continue;
        }

        bool left_boundary =
            i == 0 ||
            !is_word_character((unsigned char)sentence[i - 1]);

        bool right_boundary =
            i + word_length == sentence_length ||
            !is_word_character((unsigned char)sentence[i + word_length]);

        if (left_boundary && right_boundary) {
            return true;
        }
    }

    return false;
}

static bool ensure_capacity(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0) {
        return false;
    }

    if (required <= *capacity) {
        return true;
    }

    size_t new_capacity = *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return false;
    }

    char *new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return false;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return true;
}

static char *read_line(FILE *stream, size_t *length)
{
    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0;

    size_t capacity = 128;
    size_t used = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return NULL;
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
                    return NULL;
                }
            } else if (next != '\n') {
                if (ungetc(next, stream) == EOF) {
                    free(buffer);
                    return NULL;
                }
            }

            break;
        }

        if (used > SIZE_MAX - 2) {
            free(buffer);
            return NULL;
        }

        if (!ensure_capacity(&buffer, &capacity, used + 2)) {
            free(buffer);
            return NULL;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    if (used == SIZE_MAX ||
        !ensure_capacity(&buffer, &capacity, used + 1)) {
        free(buffer);
        return NULL;
    }

    buffer[used] = '\0';
    *length = used;
    return buffer;
}

int main(void)
{
    size_t sentence_length = 0;
    size_t word_length = 0;

    char *sentence = read_line(stdin, &sentence_length);

    if (sentence == NULL) {
        return EXIT_FAILURE;
    }

    char *word = read_line(stdin, &word_length);

    if (word == NULL || word_length == 0) {
        free(word);
        free(sentence);
        return EXIT_FAILURE;
    }

    bool found =
        contains_word(sentence, sentence_length, word, word_length);

    int result = puts(found ? "Word is present." : "Word is not present.");

    free(word);
    free(sentence);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}