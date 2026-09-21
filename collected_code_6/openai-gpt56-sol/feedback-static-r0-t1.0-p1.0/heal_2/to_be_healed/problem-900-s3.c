#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(const char *prompt, char **line)
{
    if (prompt == NULL || line == NULL) {
        return false;
    }

    *line = NULL;

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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

        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                return false;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

static bool string_starts_with_number(const char *string, const char *number)
{
    if (string == NULL || number == NULL || *number == '\0') {
        return false;
    }

    while (*number != '\0') {
        if (*string == '\0' || *string != *number) {
            return false;
        }

        ++string;
        ++number;
    }

    return true;
}

int main(void)
{
    char *string = NULL;
    char *number = NULL;
    int status = EXIT_FAILURE;

    if (!read_line("Enter a string: ", &string)) {
        goto cleanup;
    }

    if (!read_line("Enter the starting number: ", &number)) {
        goto cleanup;
    }

    if (*number == '\0') {
        if (fputs("The number must not be empty.\n", stderr) == EOF) {
            goto cleanup;
        }
        goto cleanup;
    }

    if (string_starts_with_number(string, number)) {
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