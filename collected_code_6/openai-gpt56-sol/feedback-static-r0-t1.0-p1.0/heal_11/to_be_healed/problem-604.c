#include <limits.h>
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
    size_t cursor = 0U;

    if (string == NULL || length < 2U) {
        return;
    }

    reverse_range(string, string + length - 1U);

    while (cursor < length) {
        size_t word_start;

        while (cursor < length && is_space(string[cursor])) {
            ++cursor;
        }

        word_start = cursor;

        while (cursor < length && !is_space(string[cursor])) {
            ++cursor;
        }

        if (cursor > word_start) {
            reverse_range(string + word_start, string + cursor - 1U);
        }
    }
}

int main(void)
{
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    char *line;
    size_t length = 0U;
    int status = EXIT_FAILURE;

    if (capacity > (size_t)INT_MAX) {
        return EXIT_FAILURE;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(line, (int)capacity, stdin) == NULL) {
        if (!ferror(stdin)) {
            status = EXIT_SUCCESS;
        }
    } else {
        while (length < capacity && line[length] != '\0' &&
               line[length] != '\n') {
            ++length;
        }

        if (length < capacity && line[length] == '\n') {
            line[length] = '\0';
            status = EXIT_SUCCESS;
        } else if (length < (size_t)MAX_INPUT_LENGTH) {
            status = EXIT_SUCCESS;
        } else if (length == (size_t)MAX_INPUT_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next == '\n') {
                status = EXIT_SUCCESS;
            } else if (next == EOF && !ferror(stdin)) {
                status = EXIT_SUCCESS;
            }
        }
    }

    if (status == EXIT_SUCCESS) {
        reverse_words(line, length);

        if (fwrite(line, 1U, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(line);
    return status;
}