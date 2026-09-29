#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int is_adverb(const char *word, size_t length)
{
    static const char *const exceptions[] = {
        "daily", "early", "fast", "hard", "late", "long",
        "monthly", "straight", "weekly", "well", "yearly"
    };
    const size_t count = sizeof(exceptions) / sizeof(exceptions[0]);
    size_t i;

    for (i = 0U; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t exception_length = strlen(exceptions[i]);

        if (length == exception_length &&
            memcmp(word, exceptions[i], length) == 0) {
            return 1;
        }
    }

    return length > 2U &&
           word[length - 2U] == 'l' &&
           word[length - 1U] == 'y';
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
            printf("%.*s: position %zu\n",
                   /* Possible weaknesses found:
                    *  use of undeclared identifier 'INT_MAX'
                    *  'INT_MAX' undeclared (first use in this function)
                    *  each undeclared identifier is reported only once for each function it appears in
                    */
                   (int)(length > (size_t)INT_MAX ? INT_MAX : length),
                   sentence + start,
                   start);
        }

        free(word);
    }

    return 1;
}

int main(void)
{
    char *sentence = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX) {
            free(sentence);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_sentence;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(sentence);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_sentence = realloc(sentence, new_capacity);
            if (new_sentence == NULL) {
                free(sentence);
                fputs("Memory allocation failed.\n", stderr);
                return EXIT_FAILURE;
            }

            sentence = new_sentence;
            capacity = new_capacity;
        }

        sentence[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(sentence);
        fputs("Input error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sentence == NULL) {
        sentence = malloc(1U);
        if (sentence == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
        capacity = 1U;
    }

    if (length >= capacity) {
        char *new_sentence;

        if (length == SIZE_MAX) {
            free(sentence);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        new_sentence = realloc(sentence, length + 1U);
        if (new_sentence == NULL) {
            free(sentence);
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }

        sentence = new_sentence;
    }

    sentence[length] = '\0';

    if (!find_adverbs(sentence, length)) {
        free(sentence);
        return EXIT_FAILURE;
    }

    free(sentence);
    return EXIT_SUCCESS;
}