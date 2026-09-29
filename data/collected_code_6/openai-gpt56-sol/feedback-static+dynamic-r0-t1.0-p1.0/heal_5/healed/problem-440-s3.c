#include <ctype.h>
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
        size_t room = (size_t)MAX_INPUT_LENGTH - length;
        size_t request = room < sizeof(buffer) ? room + 1 : sizeof(buffer);
        size_t count;
        size_t line_length;
        unsigned char *newline;

        if (room == 0) {
            int ch = fgetc(stdin);

            if (ch == EOF) {
                if (ferror(stdin)) {
                    fputs("Input error.\n", stderr);
                    goto cleanup;
                }
                break;
            }

            if (ch == '\n') {
                break;
            }

            fputs("Input is too large.\n", stderr);
            goto cleanup;
        }

        count = fread(buffer, 1, request, stdin);

        if (count == 0) {
            if (ferror(stdin)) {
                fputs("Input error.\n", stderr);
                goto cleanup;
            }
            break;
        }

        newline = memchr(buffer, '\n', count);
        line_length = newline == NULL
                          ? count
                          : (size_t)(newline - buffer);

        if (line_length > room) {
            fputs("Input is too large.\n", stderr);
            goto cleanup;
        }

        if (line_length != 0) {
            size_t required = length + line_length;

            if (required > capacity) {
                size_t new_capacity = capacity == 0 ? 128 : capacity;
                char *resized;

                while (new_capacity < required) {
                    if (new_capacity > (size_t)MAX_INPUT_LENGTH / 2) {
                        new_capacity = (size_t)MAX_INPUT_LENGTH;
                        break;
                    }
                    new_capacity *= 2;
                }

                if (new_capacity < required ||
                    new_capacity > (size_t)MAX_INPUT_LENGTH) {
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

            memcpy(sentence + length, buffer, line_length);
            length += line_length;
        }

        if (newline != NULL) {
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