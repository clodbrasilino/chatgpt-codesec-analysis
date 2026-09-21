#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 1023U

static bool discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static bool read_line(char **output)
{
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    char *buffer;
    size_t length;
    int ch;

    if (output == NULL || capacity > (size_t)INT_MAX) {
        return false;
    }

    *output = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return false;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\r') {
        if (buffer[length + 1U] == '\n') {
            buffer[length] = '\0';
        } else if (buffer[length + 1U] == '\0') {
            ch = fgetc(stdin);
            if (ch != '\n' && ch != EOF) {
                if (!discard_line()) {
                    free(buffer);
                    return false;
                }
                free(buffer);
                return false;
            }
            if (ferror(stdin)) {
                free(buffer);
                return false;
            }
            buffer[length] = '\0';
        }
    } else if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else {
        if (length > (size_t)MAX_INPUT_LENGTH) {
            if (!discard_line()) {
                free(buffer);
                return false;
            }
            free(buffer);
            return false;
        }

        ch = fgetc(stdin);
        if (ch == '\r') {
            ch = fgetc(stdin);
            if (ch != '\n' && ch != EOF) {
                if (!discard_line()) {
                    free(buffer);
                    return false;
                }
                free(buffer);
                return false;
            }
        } else if (ch != '\n' && ch != EOF) {
            if (!discard_line()) {
                free(buffer);
                return false;
            }
            free(buffer);
            return false;
        }

        if (ferror(stdin)) {
            free(buffer);
            return false;
        }
    }

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

    combined_size = (first_length * 2U) + 1U;
    combined = malloc(combined_size);
    if (combined == NULL) {
        return false;
    }

    if (first_length > combined_size - 1U ||
        first_length > combined_size - first_length - 1U) {
        free(combined);
        return false;
    }

    memcpy(combined, first, first_length);
    memcpy(combined + first_length, first, first_length);
    combined[combined_size - 1U] = '\0';

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