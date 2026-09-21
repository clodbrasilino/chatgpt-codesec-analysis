#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int ends_with_ly(const char *word, size_t length)
{
    return length > 2 &&
           tolower((unsigned char)word[length - 2]) == 'l' &&
           tolower((unsigned char)word[length - 1]) == 'y';
}

static void find_adverbs(const char *sentence, size_t sentence_length)
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

        if (ends_with_ly(sentence + start, length)) {
            printf("%.*s: word %zu, character %zu\n",
                   (int)length, sentence + start,
                   word_position, start + 1);
        }
    }
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };
    char *sentence;
    size_t capacity = 128;
    size_t length = 0;
    int character;

    sentence = malloc(capacity);
    if (sentence == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    fputs("Enter a sentence: ", stdout);
    if (fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'length<MAX_INPUT_LENGTH' is not redundant
     */
    while (length < MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (character == EOF || character == '\n') {
            break;
        }

        /* Possible weaknesses found:
         *  Assuming that condition 'length==capacity' is not redundant
         */
        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            /* Possible weaknesses found:
             *  Condition 'capacity>=MAX_INPUT_LENGTH' is always false [knownConditionTrueFalse]
             *  Condition 'capacity>=MAX_INPUT_LENGTH' is always false
             */
            if (capacity >= MAX_INPUT_LENGTH) {
                break;
            }

            new_capacity = capacity * 2;
            if (new_capacity > MAX_INPUT_LENGTH) {
                new_capacity = MAX_INPUT_LENGTH;
            }

            resized = realloc(sentence, new_capacity);
            if (resized == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                free(sentence);
                return EXIT_FAILURE;
            }

            sentence = resized;
            capacity = new_capacity;
        }

        sentence[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        fputs("Input error.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    if (length == MAX_INPUT_LENGTH &&
        character != EOF && character != '\n') {
        fputs("Input is too large.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    find_adverbs(sentence, length);

    if (ferror(stdout)) {
        fputs("Output error.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    free(sentence);
    return EXIT_SUCCESS;
}