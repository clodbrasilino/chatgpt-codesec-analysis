#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int ends_with_alphanumeric(const char *string, bool *result)
{
    const unsigned char *cursor;
    const unsigned char *last = NULL;

    if (string == NULL || result == NULL) {
        return -1;
    }

    for (cursor = (const unsigned char *)string; *cursor != '\0'; ++cursor) {
        last = cursor;
    }

    *result = last != NULL && isalnum(*last) != 0;
    return 0;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character = EOF;

    if (stream == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length) {
                free(buffer);
                return NULL;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream) || (character == EOF && length == 0)) {
        free(buffer);
        return NULL;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return NULL;
    }

    if (capacity < length + 1) {
        char *resized = realloc(buffer, length + 1);

        if (resized == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = resized;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    bool result;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ends_with_alphanumeric(input, &result) != 0) {
        free(input);
        fputs("Operation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result ? "true" : "false");
    free(input);

    return EXIT_SUCCESS;
}