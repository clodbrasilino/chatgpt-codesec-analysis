#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
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
        bool valid_start;
        bool valid_end;

        if (memcmp(sentence + i, word, word_length) != 0) {
            continue;
        }

        valid_start =
            i == 0 || !is_word_character((unsigned char)sentence[i - 1]);

        valid_end =
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
    char *line;
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

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return false;
            }

            new_capacity = capacity * 2;
            resized_line = realloc(line, new_capacity);
            if (resized_line == NULL) {
                free(line);
                return false;
            }

            line = resized_line;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)character;
    }

    if (length > 0 && line[length - 1] == '\r') {
        --length;
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
    int status = EXIT_FAILURE;

    if (!read_line("Enter a sentence: ", &sentence, &sentence_length)) {
        fputs("Failed to read the sentence.\n", stderr);
        goto cleanup;
    }

    if (!read_line("Enter a word: ", &word, &word_length)) {
        fputs("Failed to read the word.\n", stderr);
        goto cleanup;
    }

    if (word_length == 0) {
        fputs("Word must not be empty.\n", stderr);
        goto cleanup;
    }

    puts(contains_word(sentence, sentence_length, word, word_length)
             ? "Word is present."
             : "Word is not present.");

    status = EXIT_SUCCESS;

cleanup:
    free(word);
    free(sentence);
    return status;
}