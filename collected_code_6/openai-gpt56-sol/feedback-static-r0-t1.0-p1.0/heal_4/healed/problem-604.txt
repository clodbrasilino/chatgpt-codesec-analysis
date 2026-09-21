#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static int is_space(char character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
}

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temporary = *start;
        *start++ = *end;
        *end-- = temporary;
    }
}

static void reverse_words(char *string, size_t length)
{
    char *cursor;
    char *end;

    if (string == NULL || length < 2U) {
        return;
    }

    reverse_range(string, string + length - 1U);

    cursor = string;
    end = string + length;

    while (cursor < end) {
        char *word_start;

        while (cursor < end && is_space(*cursor)) {
            ++cursor;
        }

        word_start = cursor;

        while (cursor < end && !is_space(*cursor)) {
            ++cursor;
        }

        if (word_start < cursor) {
            reverse_range(word_start, cursor - 1);
        }
    }
}

int main(void)
{
    char *line;
    size_t capacity = 128U;
    size_t length = 0U;
    int status = EXIT_SUCCESS;

    line = malloc(capacity);
    if (line == NULL) {
        return EXIT_FAILURE;
    }

    while (length < (size_t)MAX_INPUT_LENGTH) {
        int character = getchar();

        if (character == EOF || character == '\n') {
            break;
        }

        if (length + 1U >= capacity) {
            size_t maximum_capacity = (size_t)MAX_INPUT_LENGTH + 1U;
            size_t new_capacity;
            char *resized_line;

            if (capacity >= maximum_capacity) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            if (capacity > maximum_capacity / 2U) {
                new_capacity = maximum_capacity;
            } else {
                new_capacity = capacity * 2U;
            }

            resized_line = realloc(line, new_capacity);
            if (resized_line == NULL) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            line = resized_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (ferror(stdin)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (length == (size_t)MAX_INPUT_LENGTH) {
        int character = getchar();

        if (character != EOF && character != '\n') {
            status = EXIT_FAILURE;
            goto cleanup;
        }

        if (character == EOF && ferror(stdin)) {
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    line[length] = '\0';
    reverse_words(line, length);

    if (fwrite(line, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        status = EXIT_FAILURE;
    }

cleanup:
    free(line);
    return status;
}