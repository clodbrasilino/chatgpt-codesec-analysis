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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
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

    sentence = read_line("Enter a sentence: ");
    if (sentence == NULL) {
        fputs("Failed to read the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    word = read_line("Enter a word: ");
    if (word == NULL) {
        fputs("Failed to read the word.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    if (*word == '\0') {
        fputs("Word must not be empty.\n", stderr);
        free(word);
        free(sentence);
        return EXIT_FAILURE;
    }

    puts(contains_word(sentence, word)
             ? "Word is present."
             : "Word is not present.");

    free(word);
    free(sentence);
    return EXIT_SUCCESS;
}