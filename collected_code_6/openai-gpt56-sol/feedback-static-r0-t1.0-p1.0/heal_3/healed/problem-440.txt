#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_adverb(const char *word, size_t length)
{
    static const struct {
        const char *word;
        size_t length;
    } exceptions[] = {
        {"daily", 5U},
        {"early", 5U},
        {"fast", 4U},
        {"hard", 4U},
        {"late", 4U},
        {"long", 4U},
        {"monthly", 7U},
        {"straight", 8U},
        {"weekly", 6U},
        {"well", 4U},
        {"yearly", 6U}
    };
    const size_t count = sizeof exceptions / sizeof exceptions[0];
    size_t i;

    for (i = 0U; i < count; ++i) {
        if (length == exceptions[i].length &&
            memcmp(word, exceptions[i].word, length) == 0) {
            return 1;
        }
    }

    return length > 2U &&
           word[length - 2U] == 'l' &&
           word[length - 1U] == 'y';
}

static int print_word(const char *word, size_t length)
{
    size_t offset = 0U;

    while (offset < length) {
        size_t remaining = length - offset;
        int chunk = remaining > (size_t)INT_MAX
                        ? INT_MAX
                        : (int)remaining;

        if (printf("%.*s", chunk, word + offset) < 0) {
            return 0;
        }

        offset += (size_t)chunk;
    }

    return 1;
}

static int find_adverbs(const char *sentence, size_t sentence_length)
{
    size_t i = 0U;

    while (i < sentence_length) {
        size_t start;
        size_t length;
        char *word;
        size_t j;

        while (i < sentence_length &&
               !isalnum((unsigned char)sentence[i]) &&
               sentence[i] != '\'') {
            ++i;
        }

        if (i == sentence_length) {
            break;
        }

        start = i;

        while (i < sentence_length &&
               (isalnum((unsigned char)sentence[i]) ||
                sentence[i] == '\'')) {
            ++i;
        }

        length = i - start;

        if (length == SIZE_MAX) {
            fputs("Input is too large.\n", stderr);
            return 0;
        }

        word = malloc(length + 1U);
        if (word == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return 0;
        }

        for (j = 0U; j < length; ++j) {
            word[j] = (char)tolower((unsigned char)sentence[start + j]);
        }
        word[length] = '\0';

        if (is_adverb(word, length)) {
            if (!print_word(sentence + start, length) ||
                printf(": position %zu\n", start) < 0) {
                free(word);
                fputs("Output error.\n", stderr);
                return 0;
            }
        }

        free(word);
    }

    return 1;
}

static int read_sentence(char **sentence, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 0U;
    size_t used = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (used == SIZE_MAX) {
            free(buffer);
            fputs("Input is too large.\n", stderr);
            return 0;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(buffer);
                    fputs("Input is too large.\n", stderr);
                    return 0;
                }
                new_capacity = capacity * 2U;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                fputs("Memory allocation failed.\n", stderr);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        fputs("Input error.\n", stderr);
        return 0;
    }

    if (buffer == NULL) {
        buffer = malloc(1U);
        if (buffer == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return 0;
        }
    }

    buffer[used] = '\0';
    *sentence = buffer;
    *length = used;

    return 1;
}

int main(void)
{
    char *sentence;
    size_t length;

    if (!read_sentence(&sentence, &length)) {
        return EXIT_FAILURE;
    }

    if (!find_adverbs(sentence, length)) {
        free(sentence);
        return EXIT_FAILURE;
    }

    free(sentence);

    if (fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}