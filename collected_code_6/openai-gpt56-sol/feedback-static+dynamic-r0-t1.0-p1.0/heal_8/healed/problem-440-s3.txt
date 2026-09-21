#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH (1024U * 1024U)
#define INITIAL_CAPACITY 128U

static int ends_with_ly(const char *word, size_t length)
{
    return length > 2U &&
           tolower((unsigned char)word[length - 2U]) == 'l' &&
           tolower((unsigned char)word[length - 1U]) == 'y';
}

static int find_adverbs(const char *sentence, size_t length)
{
    size_t i = 0U;
    size_t word_position = 0U;

    while (i < length) {
        size_t start;
        size_t word_length;

        while (i < length && !isalpha((unsigned char)sentence[i])) {
            ++i;
        }

        if (i == length) {
            break;
        }

        start = i;

        while (i < length &&
               (isalpha((unsigned char)sentence[i]) ||
                sentence[i] == '\'' ||
                sentence[i] == '-')) {
            ++i;
        }

        word_length = i - start;
        ++word_position;

        if (ends_with_ly(sentence + start, word_length)) {
            if (fwrite(sentence + start, 1U, word_length, stdout) !=
                    word_length ||
                fprintf(stdout, ": word %zu, character %zu\n",
                        word_position, start + 1U) < 0) {
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

    if (buffer == NULL || capacity == NULL ||
        required > MAX_INPUT_LENGTH) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity;

    if (new_capacity == 0U) {
        new_capacity = INITIAL_CAPACITY;
    }

    if (new_capacity > MAX_INPUT_LENGTH) {
        return -1;
    }

    while (new_capacity < required) {
        if (new_capacity > MAX_INPUT_LENGTH / 2U) {
            new_capacity = MAX_INPUT_LENGTH;
            break;
        }

        new_capacity *= 2U;
    }

    if (new_capacity < required || new_capacity > MAX_INPUT_LENGTH) {
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
    size_t capacity = 0U;
    int ch;

    if (sentence == NULL || length == NULL) {
        return -1;
    }

    *sentence = NULL;
    *length = 0U;

    while ((ch = fgetc(stdin)) != EOF) {
        size_t required;
        int result;

        if (ch == '\n') {
            return 0;
        }

        if (*length == MAX_INPUT_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                return -3;
            }

            return -1;
        }

        required = *length + 1U;
        result = grow_buffer(sentence, &capacity, required);

        if (result != 0) {
            return result;
        }

        (*sentence)[*length] = (char)(unsigned char)ch;
        *length = required;
    }

    return ferror(stdin) ? -3 : 0;
}

int main(void)
{
    char *sentence = NULL;
    size_t length = 0U;
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