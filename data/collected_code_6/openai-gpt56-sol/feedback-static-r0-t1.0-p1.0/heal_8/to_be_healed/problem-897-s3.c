#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
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

    for (size_t index = 0; index <= last_start; ++index) {
        if (memcmp(sentence + index, word, word_length) != 0) {
            continue;
        }

        bool valid_start =
            index == 0 ||
            !is_word_character((unsigned char)sentence[index - 1]);

        bool valid_end =
            index == last_start ||
            !is_word_character((unsigned char)sentence[index + word_length]);

        if (valid_start && valid_end) {
            return true;
        }
    }

    return false;
}

static char *read_line(FILE *stream, size_t *line_length)
{
    if (stream == NULL || line_length == NULL) {
        return NULL;
    }

    *line_length = 0;

    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line_length = length;

    return buffer;
}

int main(void)
{
    size_t sentence_length;
    size_t word_length;

    char *sentence = read_line(stdin, &sentence_length);
    if (sentence == NULL) {
        fputs("Failed to read the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    char *word = read_line(stdin, &word_length);
    if (word == NULL) {
        fputs("Failed to read the word.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    puts(contains_word(sentence, sentence_length, word, word_length)
             ? "Present"
             : "Not present");

    free(word);
    free(sentence);

    return EXIT_SUCCESS;
}