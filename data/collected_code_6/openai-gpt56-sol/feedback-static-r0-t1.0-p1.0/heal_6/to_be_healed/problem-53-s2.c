#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { INITIAL_CAPACITY = 128 };

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t used = 0U;
    char *data;
    int character = EOF;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stream) == EOF) {
                    free(data);
                    return -1;
                }
            }

            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(data, new_capacity);
            if (resized == NULL) {
                free(data);
                return -1;
            }

            data = resized;
            capacity = new_capacity;
        }

        data[used++] = (char)(unsigned char)character;
    }

    if (ferror(stream)) {
        free(data);
        return -1;
    }

    if (character == EOF && used == 0U) {
        free(data);
        return 0;
    }

    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    int status = read_line(stdin, &input, &length);

    if (status == 0) {
        return EXIT_FAILURE;
    }

    if (status < 0) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}