#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 1023U

static bool read_line(char **output)
{
    char *buffer;
    size_t length = 0U;
    bool too_long = false;
    int ch;

    if (output == NULL) {
        return false;
    }

    *output = NULL;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return false;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    free(buffer);
                    return false;
                }
            }

            if (next == EOF && ferror(stdin)) {
                free(buffer);
                return false;
            }

            break;
        }

        if (length < (size_t)MAX_INPUT_LENGTH) {
            buffer[length++] = (char)ch;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin) || (ch == EOF && length == 0U && !too_long)) {
        free(buffer);
        return false;
    }

    if (too_long) {
        while (ch != '\n' && ch != EOF) {
            ch = fgetc(stdin);
        }

        free(buffer);
        return false;
    }

    buffer[length] = '\0';

    {
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
    size_t combined_size;
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

    combined_size = first_length * 2U + 1U;
    combined = malloc(combined_size);
    if (combined == NULL) {
        return false;
    }

    memcpy(combined, first, first_length);
    memcpy(combined + first_length, first, first_length);
    combined[first_length * 2U] = '\0';

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

    if (result) {
        puts("The strings are rotations of each other.");
    } else {
        puts("The strings are not rotations of each other.");
    }

    return EXIT_SUCCESS;
}