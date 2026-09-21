#include <stdio.h>
#include <stdlib.h>

static int is_space(char character)
{
    return character == ' ' || character == '\t' || character == '\n' ||
           character == '\r' || character == '\f' || character == '\v';
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
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;
    int status = EXIT_SUCCESS;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == SIZE_MAX - 1U) {
            status = EXIT_FAILURE;
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    new_capacity = length + 2U;
                } else {
                    new_capacity = capacity * 2U;
                }
            }

            if (new_capacity <= length + 1U) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (ferror(stdin)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (line == NULL) {
        line = malloc(1U);
        if (line == NULL) {
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    line[length] = '\0';
    reverse_words(line, length);

    if (puts(line) == EOF) {
        status = EXIT_FAILURE;
    }

cleanup:
    free(line);
    return status;
}