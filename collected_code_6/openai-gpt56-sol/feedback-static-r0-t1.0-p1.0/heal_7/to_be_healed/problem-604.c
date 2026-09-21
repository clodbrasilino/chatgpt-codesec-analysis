#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH (1024U * 1024U)

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
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    char *line = NULL;
    size_t length = 0U;
    int status = EXIT_FAILURE;

    if (capacity > (size_t)INT32_MAX) {
        return EXIT_FAILURE;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(line, (int)capacity, stdin) == NULL) {
        if (!ferror(stdin)) {
            line[0] = '\0';
            status = EXIT_SUCCESS;
        }
    } else {
        while (length < capacity && line[length] != '\0' &&
               line[length] != '\n') {
            ++length;
        }

        if (length >= capacity) {
            status = EXIT_FAILURE;
        } else if (line[length] == '\n') {
            line[length] = '\0';
            status = EXIT_SUCCESS;
        } else if (length < (size_t)MAX_INPUT_LENGTH) {
            status = EXIT_SUCCESS;
        } else if (length == (size_t)MAX_INPUT_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int character = fgetc(stdin);

            if (character == '\n') {
                status = EXIT_SUCCESS;
            } else if (character == EOF && !ferror(stdin)) {
                status = EXIT_SUCCESS;
            }
        }
    }

    if (status == EXIT_SUCCESS) {
        reverse_words(line, length);

        if (fwrite(line, sizeof(*line), length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(line);
    return status;
}