#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static int ends_with_ly(const char *word, size_t length)
{
    return length > 2 &&
           tolower((unsigned char)word[length - 2]) == 'l' &&
           tolower((unsigned char)word[length - 1]) == 'y';
}

static int print_word(const char *word, size_t length,
                      size_t word_position, size_t character_position)
{
    if (length > (size_t)INT_MAX) {
        return 0;
    }

    return printf("%.*s: word %zu, character %zu\n",
                  (int)length, word, word_position,
                  character_position) >= 0;
}

static int find_adverbs(const char *sentence, size_t sentence_length)
{
    size_t i = 0;
    size_t word_position = 0;

    while (i < sentence_length) {
        size_t start;
        size_t length;

        while (i < sentence_length &&
               !isalpha((unsigned char)sentence[i])) {
            ++i;
        }

        if (i == sentence_length) {
            break;
        }

        start = i;

        while (i < sentence_length &&
               (isalpha((unsigned char)sentence[i]) ||
                sentence[i] == '\'' ||
                sentence[i] == '-')) {
            ++i;
        }

        length = i - start;
        ++word_position;

        if (ends_with_ly(sentence + start, length) &&
            !print_word(sentence + start, length,
                        word_position, start + 1)) {
            return 0;
        }
    }

    return 1;
}

static int read_sentence(char **sentence, size_t *sentence_length)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (sentence == NULL || sentence_length == NULL) {
        return 0;
    }

    *sentence = NULL;
    *sentence_length = 0;

    if (capacity > (size_t)MAX_INPUT_LENGTH) {
        capacity = (size_t)MAX_INPUT_LENGTH;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return 0;
    }

    while (length < (size_t)MAX_INPUT_LENGTH) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                fputs("Input error.\n", stderr);
                free(buffer);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t remaining = (size_t)MAX_INPUT_LENGTH - capacity;
            size_t growth = capacity;
            size_t new_capacity;
            char *resized;

            if (remaining == 0) {
                free(buffer);
                return 0;
            }

            if (growth > remaining) {
                growth = remaining;
            }

            new_capacity = capacity + growth;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (length == (size_t)MAX_INPUT_LENGTH) {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            fputs("Input is too large.\n", stderr);
            free(buffer);
            return 0;
        }

        if (character == EOF && ferror(stdin)) {
            fputs("Input error.\n", stderr);
            free(buffer);
            return 0;
        }
    }

    *sentence = buffer;
    *sentence_length = length;
    return 1;
}

int main(void)
{
    char *sentence = NULL;
    size_t length = 0;

    if (fputs("Enter a sentence: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_sentence(&sentence, &length)) {
        return EXIT_FAILURE;
    }

    if (!find_adverbs(sentence, length) || fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    free(sentence);
    return EXIT_SUCCESS;
}