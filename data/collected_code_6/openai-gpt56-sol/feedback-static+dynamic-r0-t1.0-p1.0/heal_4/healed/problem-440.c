#include <ctype.h>
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
        {"daily", 5},
        {"early", 5},
        {"fast", 4},
        {"hard", 4},
        {"late", 4},
        {"long", 4},
        {"monthly", 7},
        {"straight", 8},
        {"weekly", 6},
        {"well", 4},
        {"yearly", 6}
    };

    for (size_t i = 0; i < sizeof exceptions / sizeof exceptions[0]; ++i) {
        if (length == exceptions[i].length &&
            memcmp(word, exceptions[i].word, length) == 0) {
            return 1;
        }
    }

    return length > 2 &&
           word[length - 2] == 'l' &&
           word[length - 1] == 'y';
}

static int print_adverb(const char *word, size_t length, size_t position)
{
    if (fwrite(word, 1, length, stdout) != length ||
        fprintf(stdout, ": position %zu\n", position) < 0) {
        fputs("Output error.\n", stderr);
        return 0;
    }

    return 1;
}

static int find_adverbs(const char *sentence, size_t sentence_length)
{
    size_t i = 0;

    while (i < sentence_length) {
        while (i < sentence_length &&
               !isalnum((unsigned char)sentence[i]) &&
               sentence[i] != '\'') {
            ++i;
        }

        if (i == sentence_length) {
            break;
        }

        size_t start = i;

        while (i < sentence_length &&
               (isalnum((unsigned char)sentence[i]) ||
                sentence[i] == '\'')) {
            ++i;
        }

        size_t length = i - start;

        if (length == SIZE_MAX) {
            fputs("Word is too large.\n", stderr);
            return 0;
        }

        char *normalized = malloc(length + 1);
        if (normalized == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return 0;
        }

        for (size_t j = 0; j < length; ++j) {
            normalized[j] =
                (char)tolower((unsigned char)sentence[start + j]);
        }
        normalized[length] = '\0';

        int adverb = is_adverb(normalized, length);
        free(normalized);

        if (adverb && !print_adverb(sentence + start, length, start)) {
            return 0;
        }
    }

    return 1;
}

static int read_sentence(char **sentence, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t used = 0;

    for (;;) {
        int ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            fputs("Input is too large.\n", stderr);
            return 0;
        }

        if (used + 1 >= capacity) {
            size_t required = used + 2;
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity < capacity || new_capacity < required) {
                free(buffer);
                fputs("Input is too large.\n", stderr);
                return 0;
            }

            char *temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                fputs("Memory allocation failed.\n", stderr);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        fputs("Input error.\n", stderr);
        return 0;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
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
    char *sentence = NULL;
    size_t length = 0;

    if (!read_sentence(&sentence, &length)) {
        return EXIT_FAILURE;
    }

    int success = find_adverbs(sentence, length);
    free(sentence);

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}