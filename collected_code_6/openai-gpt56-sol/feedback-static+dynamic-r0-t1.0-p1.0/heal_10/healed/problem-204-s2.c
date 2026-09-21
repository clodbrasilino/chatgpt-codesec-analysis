#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_character(const char *string, unsigned char character)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if ((unsigned char)*string == character) {
            ++count;
        }
        ++string;
    }

    return count;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 64;
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
        int ch;

        if (used >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[used++] = (char)ch;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 1;
}

int main(void)
{
    char *input = NULL;
    char *target = NULL;
    size_t input_length = 0;
    size_t target_length = 0;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &input_length)) {
        fputs("Failed to read the string.\n", stderr);
        goto cleanup;
    }

    if (!read_line(stdin, &target, &target_length)) {
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

    printf("%zu\n", count_character(input, (unsigned char)target[0]));
    status = EXIT_SUCCESS;

cleanup:
    free(target);
    free(input);
    return status;
}