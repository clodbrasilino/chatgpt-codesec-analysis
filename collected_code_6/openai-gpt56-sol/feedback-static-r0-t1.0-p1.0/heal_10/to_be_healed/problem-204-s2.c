#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_character(const char *string, size_t length,
                              unsigned char character)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if ((unsigned char)string[i] == character) {
            ++count;
        }
    }

    return count;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return 0;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int character;

        if (used >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 1;
}

int main(void)
{
    char *input = NULL;
    char *target_input = NULL;
    size_t input_length = 0;
    size_t target_length = 0;
    size_t count;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &input_length)) {
        fputs("Failed to read the string.\n", stderr);
        goto cleanup;
    }

    if (!read_line(stdin, &target_input, &target_length)) {
        fputs("Failed to read the character.\n", stderr);
        goto cleanup;
    }

    if (target_length != 1) {
        if (target_length == 0) {
            fputs("No character was provided.\n", stderr);
        } else {
            fputs("Provide exactly one character.\n", stderr);
        }
        goto cleanup;
    }

    count = count_character(input, input_length,
                            (unsigned char)target_input[0]);

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write the result.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(target_input);
    free(input);
    return status;
}