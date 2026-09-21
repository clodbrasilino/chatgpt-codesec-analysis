#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_word_character(unsigned char c)
{
    return isalnum(c) != 0 || c == '_';
}

static bool contains_word(const char *sentence, const char *word)
{
    size_t word_length;
    const char *match;

    if (sentence == NULL || word == NULL || word[0] == '\0') {
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
        bool valid_end = !is_word_character((unsigned char)match[word_length]);

        if (valid_start && valid_end) {
            return true;
        }

        ++match;
    }

    return false;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;
    int character;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n' && character != EOF) {
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

    if (ferror(stream) != 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *sentence;
    char *word;
    bool found;

    sentence = read_line(stdin);
    if (sentence == NULL) {
        fputs("Failed to read the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    word = read_line(stdin);
    if (word == NULL) {
        fputs("Failed to read the word.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    found = contains_word(sentence, word);
    puts(found ? "Present" : "Not present");

    free(word);
    free(sentence);
    return EXIT_SUCCESS;
}