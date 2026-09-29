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
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };
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
        unsigned char buffer[4096];
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);
        size_t line_bytes = 0;

        while (line_bytes < bytes_read && buffer[line_bytes] != '\n') {
            ++line_bytes;
        }

        if (line_bytes > MAX_INPUT_LENGTH - length) {
            fputs("Input is too large.\n", stderr);
            goto cleanup;
        }

        if (line_bytes != 0) {
            size_t required = length + line_bytes;

            if (required > capacity) {
                size_t new_capacity = capacity == 0 ? 128 : capacity;
                char *resized;

                while (new_capacity < required) {
                    if (new_capacity > MAX_INPUT_LENGTH / 2) {
                        new_capacity = MAX_INPUT_LENGTH;
                        break;
                    }
                    new_capacity *= 2;
                }

                if (new_capacity < required) {
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

            for (size_t i = 0; i < line_bytes; ++i) {
                sentence[length + i] = (char)buffer[i];
            }
            length += line_bytes;
        }

        if (line_bytes < bytes_read) {
            break;
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                fputs("Input error.\n", stderr);
                goto cleanup;
            }
            break;
        }
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