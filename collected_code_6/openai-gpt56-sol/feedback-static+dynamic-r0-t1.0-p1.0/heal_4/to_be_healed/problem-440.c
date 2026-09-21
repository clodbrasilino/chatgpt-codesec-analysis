#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_adverb(const char *word, size_t length)
{
    static const char *const exceptions[] = {
        "daily", "early", "fast", "hard", "late", "long",
        "monthly", "straight", "weekly", "well", "yearly"
    };
    size_t count = sizeof exceptions / sizeof exceptions[0];

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t exception_length = strlen(exceptions[i]);

        if (length == exception_length &&
            memcmp(word, exceptions[i], length) == 0) {
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
        printf(": position %zu\n", position) < 0) {
        fputs("Output error.\n", stderr);
        return 0;
    }

    return 1;
}

static int find_adverbs(const char *sentence, size_t sentence_length)
{
    size_t i = 0;

    while (i < sentence_length) {
        size_t start;
        size_t length;
        char *normalized;

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

        if (length > SIZE_MAX - 1) {
            fputs("Word is too large.\n", stderr);
            return 0;
        }

        normalized = malloc(length + 1);
        if (normalized == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return 0;
        }

        for (size_t j = 0; j < length; ++j) {
            normalized[j] =
                (char)tolower((unsigned char)sentence[start + j]);
        }
        normalized[length] = '\0';

        if (is_adverb(normalized, length) &&
            !print_adverb(sentence + start, length, start)) {
            free(normalized);
            return 0;
        }

        free(normalized);
    }

    return 1;
}

static int read_sentence(char **sentence, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t used = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (used == SIZE_MAX - 1) {
            free(buffer);
            fputs("Input is too large.\n", stderr);
            return 0;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    fputs("Input is too large.\n", stderr);
                    return 0;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity <= used + 1) {
                free(buffer);
                fputs("Input is too large.\n", stderr);
                return 0;
            }

            temporary = realloc(buffer, new_capacity);
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
    return EXIT_SUCCESS;
}