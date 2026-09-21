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

    const size_t last_position = sentence_length - word_length;

    for (size_t position = 0; position <= last_position; ++position) {
        if (memcmp(sentence + position, word, word_length) != 0) {
            continue;
        }

        const bool valid_start =
            position == 0 ||
            !is_word_character((unsigned char)sentence[position - 1]);

        const bool valid_end =
            position == last_position ||
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
    if (stream == NULL || line_length == NULL) {
        return NULL;
    }

    *line_length = 0;

    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    size_t length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char input[128];

        if (fgets(input, sizeof input, stream) == NULL) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t chunk_length = strlen(input);
        bool has_newline =
            chunk_length > 0 && input[chunk_length - 1] == '\n';

        if (has_newline) {
            --chunk_length;
        }

        if (chunk_length > SIZE_MAX - length - 1) {
            free(buffer);
            return NULL;
        }

        const size_t required = length + chunk_length + 1;

        if (required > capacity) {
            size_t new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + length, input, chunk_length);
        length += chunk_length;

        if (has_newline) {
            break;
        }
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
    size_t sentence_length = 0;
    size_t word_length = 0;

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

    const bool found =
        contains_word(sentence, sentence_length, word, word_length);

    puts(found ? "Present" : "Not present");

    free(word);
    free(sentence);

    return EXIT_SUCCESS;
}