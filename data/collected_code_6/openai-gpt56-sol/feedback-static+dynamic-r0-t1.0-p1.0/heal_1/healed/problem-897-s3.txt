#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_word_character(unsigned char c)
{
    return isalnum(c) != 0 || c == '_';
}

static bool contains_word(const char *sentence, size_t sentence_length,
                          const char *word, size_t word_length)
{
    size_t position;

    if (sentence == NULL || word == NULL || word_length == 0 ||
        word_length > sentence_length) {
        return false;
    }

    for (position = 0; position <= sentence_length - word_length; ++position) {
        bool valid_start;
        bool valid_end;

        if (memcmp(sentence + position, word, word_length) != 0) {
            continue;
        }

        valid_start = position == 0 ||
                      !is_word_character((unsigned char)sentence[position - 1]);
        valid_end = position + word_length == sentence_length ||
                    !is_word_character(
                        (unsigned char)sentence[position + word_length]);

        if (valid_start && valid_end) {
            return true;
        }
    }

    return false;
}

static char *read_line(FILE *stream, size_t *line_length)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;
    int character;

    if (stream == NULL || line_length == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        character = fgetc(stream);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
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

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    *line_length = length;
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
        fputs("Failed to read the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    word = read_line(stdin, &word_length);
    if (word == NULL) {
        fputs("Failed to read the word.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    found = contains_word(sentence, sentence_length, word, word_length);
    puts(found ? "Present" : "Not present");

    free(word);
    free(sentence);
    return EXIT_SUCCESS;
}