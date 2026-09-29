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
        if (memcmp(sentence + position, word, word_length) != 0) {
            continue;
        }

        bool valid_start =
            position == 0 ||
            !is_word_character((unsigned char)sentence[position - 1]);

        bool valid_end =
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
    char *line = NULL;
    size_t length = 0;
    size_t capacity = 128;

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

    while (fgets(line + length, (int)(capacity - length), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t bytes_read = strlen(line + length);
        length += bytes_read;

        if (length > 0 && line[length - 1] == '\n') {
            line[--length] = '\0';
            *output = line;
            *output_length = length;
            return true;
        }

        if (feof(stdin)) {
            *output = line;
            *output_length = length;
            return true;
        }

        if (capacity > SIZE_MAX / 2) {
            free(line);
            return false;
        }

        size_t new_capacity = capacity * 2;
        char *resized = realloc(line, new_capacity);

        if (resized == NULL) {
            free(line);
            return false;
        }

        line = resized;
        capacity = new_capacity;
    }

    if (ferror(stdin) || length == 0) {
        free(line);
        return false;
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

    puts(contains_word(sentence, sentence_length, word, word_length)
             ? "Word is present."
             : "Word is not present.");

    free(word);
    free(sentence);
    return EXIT_SUCCESS;
}