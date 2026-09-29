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

    *result = last != NULL && isalnum((int)*last) != 0;
    return 0;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
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