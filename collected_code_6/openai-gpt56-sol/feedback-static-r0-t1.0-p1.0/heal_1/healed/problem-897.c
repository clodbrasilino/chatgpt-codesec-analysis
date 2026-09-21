#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static bool contains_word(const char *sentence, const char *word)
{
    size_t word_length;
    const char *match;

    if (sentence == NULL || word == NULL || *word == '\0') {
        return false;
    }

    word_length = strlen(word);
    match = sentence;

    while ((match = strstr(match, word)) != NULL) {
        bool valid_start = match == sentence ||
                           !is_word_character((unsigned char)match[-1]);
        bool valid_end =
            !is_word_character((unsigned char)match[word_length]);

        if (valid_start && valid_end) {
            return true;
        }

        ++match;
    }

    return false;
}

static char *read_line(const char *prompt)
{
    char *line = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int character;

    if (prompt != NULL) {
        fputs(prompt, stdout);
        fflush(stdout);
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        char *resized;

        if (length + 1 >= capacity) {
            size_t new_capacity;

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

    if (character == EOF && length == 0) {
        free(line);
        return NULL;
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

    if (*word == '\0') {
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