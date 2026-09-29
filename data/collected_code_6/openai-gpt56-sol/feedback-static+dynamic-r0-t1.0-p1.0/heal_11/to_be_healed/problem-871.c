#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 1023U

static bool discard_remainder(int ch)
{
    while (ch != '\n' && ch != EOF) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ch != EOF || !ferror(stdin);
}

static bool read_line(char **output)
{
    char *buffer;
    size_t length = 0U;
    int ch = EOF;

    if (output == NULL) {
        return false;
    }

    *output = NULL;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (length == (size_t)MAX_INPUT_LENGTH) {
            bool discarded = discard_remainder(ch);
            free(buffer);
            return discarded && false;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stdin) == EOF) {
                free(buffer);
                return false;
            }
        } else if (next == EOF && ferror(stdin)) {
            free(buffer);
            return false;
        }
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';

    if (length < (size_t)MAX_INPUT_LENGTH) {
        char *resized = realloc(buffer, length + 1U);

        if (resized != NULL) {
            buffer = resized;
        }
    }

    *output = buffer;
    return true;
}

static bool are_rotations(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t allocation_size;
    char *combined;
    bool result;

    if (first == NULL || second == NULL) {
        return false;
    }

    first_length = strnlen(first, (size_t)MAX_INPUT_LENGTH + 1U);
    second_length = strnlen(second, (size_t)MAX_INPUT_LENGTH + 1U);

    if (first_length > (size_t)MAX_INPUT_LENGTH ||
        second_length > (size_t)MAX_INPUT_LENGTH ||
        first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    allocation_size = first_length * 2U + 1U;
    combined = malloc(allocation_size);
    if (combined == NULL) {
        return false;
    }

    memmove(combined, first, first_length);
    memmove(combined + first_length, first, first_length);
    combined[allocation_size - 1U] = '\0';

    result = strstr(combined, second) != NULL;

    free(combined);
    return result;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    bool result;

    if (!read_line(&first) || !read_line(&second)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    result = are_rotations(first, second);

    free(first);
    free(second);

    puts(result
             ? "The strings are rotations of each other."
             : "The strings are not rotations of each other.");

    return EXIT_SUCCESS;
}