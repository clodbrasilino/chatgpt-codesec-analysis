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

    for (size_t position = 0;
         position <= sentence_length - word_length;
         ++position) {
        bool valid_start;
        bool valid_end;

        if (memcmp(sentence + position, word, word_length) != 0) {
            continue;
        }

        valid_start =
            position == 0 ||
            !is_word_character((unsigned char)sentence[position - 1]);

        valid_end =
            position + word_length == sentence_length ||
            !is_word_character(
                (unsigned char)sentence[position + word_length]);

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
    int character;

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
        character = fgetc(stdin);

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
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return false;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    line[length] = '\0';
    *output = line;
    *output_length = length;
    return true;
}

int main(void)
{
    char *sentence;
    char *word;
    size_t sentence_length;
    size_t word_length;
    bool present;

    if (!read_line("Enter a sentence: ", &sentence, &sentence_length)) {
        fputs("Unable to read the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line("Enter a word: ", &word, &word_length)) {
        fputs("Unable to read the word.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    if (word_length == 0) {
        fputs("Word must not be empty.\n", stderr);
        free(word);
        free(sentence);
        return EXIT_FAILURE;
    }

    present = contains_word(sentence, sentence_length, word, word_length);
    puts(present ? "Word is present." : "Word is not present.");

    free(word);
    free(sentence);

    return EXIT_SUCCESS;
}