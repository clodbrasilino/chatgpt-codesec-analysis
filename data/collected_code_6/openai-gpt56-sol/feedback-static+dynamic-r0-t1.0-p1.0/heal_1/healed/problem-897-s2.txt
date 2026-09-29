#include <ctype.h>
#include <stdbool.h>
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
    char *buffer = NULL;
    size_t capacity = 0;
    size_t used = 0;
    int character;

    if (stream == NULL || length == NULL) {
        return NULL;
    }

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (character == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                ungetc(next, stream);
            }
            break;
        }

        if (used == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_buffer;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof *buffer) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity * sizeof *buffer);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    if (character == EOF && used == 0) {
        free(buffer);
        return NULL;
    }

    if (used == capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;
        char *new_buffer;

        if (new_capacity <= capacity) {
            free(buffer);
            return NULL;
        }

        new_buffer = realloc(buffer, new_capacity * sizeof *buffer);
        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[used] = '\0';
    *length = used;
    return buffer;
}

int main(void)
{
    char *sentence;
    char *word;
    size_t sentence_length;
    size_t word_length;
    bool found;

    sentence = read_line(stdin, &sentence_length);
    if (sentence == NULL) {
        return EXIT_FAILURE;
    }

    word = read_line(stdin, &word_length);
    if (word == NULL || word_length == 0) {
        free(sentence);
        free(word);
        return EXIT_FAILURE;
    }

    found = contains_word(sentence, sentence_length, word, word_length);

    puts(found ? "Word is present." : "Word is not present.");

    free(word);
    free(sentence);
    return EXIT_SUCCESS;
}