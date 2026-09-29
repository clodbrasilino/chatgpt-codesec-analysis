#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH (1024U * 1024U)
#define INPUT_CHUNK_SIZE 4096U

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
        size_t word_length;

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

        word_length = i - start;
        ++word_position;

        if (ends_with_ly(sentence + start, word_length)) {
            if (fwrite(sentence + start, 1, word_length, stdout) !=
                    word_length ||
                printf(": word %zu, character %zu\n",
                       word_position, start + 1) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (required > MAX_INPUT_LENGTH) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > MAX_INPUT_LENGTH / 2U) {
            new_capacity = MAX_INPUT_LENGTH;
        } else {
            new_capacity *= 2U;
        }
    }

    if (new_capacity < required ||
        new_capacity > MAX_INPUT_LENGTH ||
        new_capacity > SIZE_MAX) {
        return -1;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -2;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_sentence(char **sentence, size_t *length)
{
    unsigned char buffer[INPUT_CHUNK_SIZE];
    size_t capacity = 0;

    *sentence = NULL;
    *length = 0;

    for (;;) {
        size_t room;
        size_t request;
        size_t count;
        size_t line_length;
        unsigned char *newline;

        if (*length > MAX_INPUT_LENGTH) {
            return -1;
        }

        room = MAX_INPUT_LENGTH - *length;

        if (room == 0) {
            int ch = fgetc(stdin);

            if (ch == '\n' || ch == EOF) {
                return ch == EOF && ferror(stdin) ? -3 : 0;
            }

            return -1;
        }

        request = room < sizeof(buffer) ? room + 1U : sizeof(buffer);
        count = fread(buffer, 1, request, stdin);

        if (count == 0) {
            return ferror(stdin) ? -3 : 0;
        }

        newline = memchr(buffer, '\n', count);
        line_length = newline == NULL
                          ? count
                          : (size_t)(newline - buffer);

        if (line_length > room ||
            *length > SIZE_MAX - line_length) {
            return -1;
        }

        if (line_length != 0) {
            size_t required = *length + line_length;
            int result = grow_buffer(sentence, &capacity, required);

            if (result != 0) {
                return result;
            }

            memcpy(*sentence + *length, buffer, line_length);
            *length = required;
        }

        if (newline != NULL) {
            return 0;
        }
    }
}

int main(void)
{
    char *sentence = NULL;
    size_t length = 0;
    int result;
    int status = EXIT_FAILURE;

    if (fputs("Enter a sentence: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    result = read_sentence(&sentence, &length);

    if (result == -1) {
        fputs("Input is too large.\n", stderr);
        goto cleanup;
    }

    if (result == -2) {
        fputs("Memory allocation failed.\n", stderr);
        goto cleanup;
    }

    if (result == -3) {
        fputs("Input error.\n", stderr);
        goto cleanup;
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