#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
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

    while (fgets(buffer + length, (int)(capacity - length), stream) != NULL) {
        size_t bytes_read = 0;

        while (buffer[length + bytes_read] != '\0' &&
               buffer[length + bytes_read] != '\n') {
            ++bytes_read;
        }

        length += bytes_read;

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return buffer;
        }

        if (feof(stream)) {
            return buffer;
        }

        if (capacity > SIZE_MAX / 2) {
            free(buffer);
            return NULL;
        }

        {
            size_t new_capacity = capacity * 2;
            char *resized;

            /* Possible weaknesses found:
             *  'INT_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'INT_MAX'
             */
            if (new_capacity > (size_t)INT_MAX) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'INT_MAX'
                 */
                new_capacity = (size_t)INT_MAX;
            }

            if (new_capacity <= capacity) {
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
    }

    if (ferror(stream) || length == 0) {
        free(buffer);
        return NULL;
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