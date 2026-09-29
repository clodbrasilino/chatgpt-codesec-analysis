#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(const char *prompt, char **line, size_t *line_length)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;

    if (prompt == NULL || line == NULL || line_length == NULL) {
        return false;
    }

    *line = NULL;
    *line_length = 0;

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\0') {
            free(buffer);
            return false;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_length = length;
    return true;
}

static bool string_starts_with_number(const char *string,
                                      size_t string_length,
                                      const char *number,
                                      size_t number_length)
{
    if (string == NULL || number == NULL || number_length == 0 ||
        number_length > string_length) {
        return false;
    }

    return memcmp(string, number, number_length) == 0;
}

int main(void)
{
    char *string = NULL;
    char *number = NULL;
    size_t string_length = 0;
    size_t number_length = 0;
    int status = EXIT_FAILURE;

    if (!read_line("Enter a string: ", &string, &string_length)) {
        goto cleanup;
    }

    if (!read_line("Enter the starting number: ", &number, &number_length)) {
        goto cleanup;
    }

    if (number_length == 0) {
        if (fputs("The number must not be empty.\n", stderr) == EOF) {
            goto cleanup;
        }
        goto cleanup;
    }

    if (string_starts_with_number(string, string_length,
                                  number, number_length)) {
        if (printf("The string starts with %s.\n", number) < 0) {
            goto cleanup;
        }
    } else {
        if (printf("The string does not start with %s.\n", number) < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(number);
    free(string);
    return status;
}