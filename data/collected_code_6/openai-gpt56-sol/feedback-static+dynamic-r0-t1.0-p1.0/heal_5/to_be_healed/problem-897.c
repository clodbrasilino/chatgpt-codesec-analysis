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
        if (memcmp(sentence + i, word, word_length) != 0) {
            continue;
        }

        bool valid_start =
            i == 0 || !is_word_character((unsigned char)sentence[i - 1]);

        bool valid_end =
            i + word_length == sentence_length ||
            !is_word_character((unsigned char)sentence[i + word_length]);

        if (valid_start && valid_end) {
            return true;
        }
    }

    return false;
}

static bool read_line(const char *prompt, char **output, size_t *output_length)
{
    size_t length = 0;
    size_t capacity = 128;
    char *line;

    if (output == NULL || output_length == NULL) {
        return false;
    }

    *output = NULL;
    *output_length = 0;

    if (prompt != NULL) {
        if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
            return false;
        }
    }

    line = malloc(capacity);
    if (line == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return false;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity <= capacity) {
                free(line);
                return false;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return false;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)character;
    }

    line[length] = '\0';
    *output = line;
    *output_length = length;
    return true;
}

int main(void)
{
    char *sentence = NULL;
    char *word = NULL;
    size_t sentence_length = 0;
    size_t word_length = 0;

    if (!read_line("Enter a sentence: ", &sentence, &sentence_length)) {
        fputs("Failed to read the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line("Enter a word: ", &word, &word_length)) {
        fputs("Failed to read the word.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    if (word_length == 0) {
        fputs("Word must not be empty.\n", stderr);
        free(word);
        free(sentence);
        return EXIT_FAILURE;
    }

    puts(contains_word(sentence, sentence_length, word, word_length)
             ? "Word is present."
             : "Word is not present.");

    free(word);
    free(sentence);
    return EXIT_SUCCESS;
}