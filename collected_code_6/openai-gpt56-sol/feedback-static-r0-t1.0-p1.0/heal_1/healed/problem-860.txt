#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    int character;

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        char *resized;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2;
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

    if (length + 1 > capacity) {
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