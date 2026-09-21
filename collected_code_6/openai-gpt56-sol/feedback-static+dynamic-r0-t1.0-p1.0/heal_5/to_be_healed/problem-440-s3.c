#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ends_with_ly(const char *word, size_t length)
{
    return length > 2 &&
           tolower((unsigned char)word[length - 2]) == 'l' &&
           tolower((unsigned char)word[length - 1]) == 'y';
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

        if (ends_with_ly(sentence + start, length)) {
            if (fwrite(sentence + start, 1, length, stdout) != length ||
                printf(": word %zu, character %zu\n",
                       word_position, start + 1) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const size_t max_input_length = 1024U * 1024U;
    char *sentence = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int status = EXIT_FAILURE;

    if (fputs("Enter a sentence: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                fputs("Input error.\n", stderr);
                goto cleanup;
            }
            break;
        }

        if (length == max_input_length) {
            fputs("Input is too large.\n", stderr);
            goto cleanup;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > max_input_length / 2) {
                new_capacity = max_input_length;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity || new_capacity > max_input_length) {
                fputs("Input is too large.\n", stderr);
                goto cleanup;
            }

            resized = realloc(sentence, new_capacity);
            if (resized == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                goto cleanup;
            }

            sentence = resized;
            capacity = new_capacity;
        }

        sentence[length++] = (char)(unsigned char)ch;
    }

    if (find_adverbs(sentence, length) != 0 ||
        fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(sentence);
    return status;
}