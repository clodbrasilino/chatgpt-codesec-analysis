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

    for (size_t i = 0; i <= sentence_length - word_length; ++i) {
        bool left_boundary =
            i == 0 || !is_word_character((unsigned char)sentence[i - 1]);
        bool right_boundary =
            i + word_length == sentence_length ||
            !is_word_character((unsigned char)sentence[i + word_length]);

        if (left_boundary && right_boundary &&
            memcmp(sentence + i, word, word_length) == 0) {
            return true;
        }
    }

    return false;
}

static char *read_line(FILE *stream, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
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
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return NULL;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (used >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    buffer[used] = '\0';
    *length = used;

    return buffer;
}

int main(void)
{
    size_t sentence_length;
    size_t word_length;
    char *sentence = read_line(stdin, &sentence_length);
    char *word;
    bool found;

    if (sentence == NULL) {
        return EXIT_FAILURE;
    }

    word = read_line(stdin, &word_length);

    if (word == NULL || word_length == 0) {
        free(word);
        free(sentence);
        return EXIT_FAILURE;
    }

    found = contains_word(sentence, sentence_length, word, word_length);
    puts(found ? "Word is present." : "Word is not present.");

    free(word);
    free(sentence);

    return EXIT_SUCCESS;
}