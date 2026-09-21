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

static bool contains_word(const char *sentence, const char *word)
{
    size_t sentence_length;
    size_t word_length;

    if (sentence == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    sentence_length = strlen(sentence);
    word_length = strlen(word);

    if (word_length > sentence_length) {
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

static char *read_line(const char *prompt)
{
    size_t length = 0;
    size_t capacity = 128;
    char *line;
    int character;

    if (prompt != NULL) {
        if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
            return NULL;
        }
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF) {
        if (ferror(stdin) || length == 0) {
            free(line);
            return NULL;
        }
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *sentence;
    char *word;
    bool present;

    sentence = read_line("Enter a sentence: ");
    if (sentence == NULL) {
        fprintf(stderr, "Unable to read the sentence.\n");
        return EXIT_FAILURE;
    }

    word = read_line("Enter a word: ");
    if (word == NULL) {
        fprintf(stderr, "Unable to read the word.\n");
        free(sentence);
        return EXIT_FAILURE;
    }

    if (word[0] == '\0') {
        fprintf(stderr, "Word must not be empty.\n");
        free(word);
        free(sentence);
        return EXIT_FAILURE;
    }

    present = contains_word(sentence, word);
    puts(present ? "Word is present." : "Word is not present.");

    free(word);
    free(sentence);

    return EXIT_SUCCESS;
}