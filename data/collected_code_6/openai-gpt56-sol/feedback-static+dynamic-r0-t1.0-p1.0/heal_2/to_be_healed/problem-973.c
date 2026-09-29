#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *string, size_t first, size_t last)
{
    while (first < last) {
        char temp = string[first];
        string[first++] = string[last];
        string[last--] = temp;
    }
}

static int left_rotate(char *string, size_t length, size_t positions)
{
    if (string == NULL) {
        return -1;
    }

    if (length == 0) {
        return 0;
    }

    positions %= length;

    if (positions == 0) {
        return 0;
    }

    reverse_range(string, 0, positions - 1);
    reverse_range(string, positions, length - 1);
    reverse_range(string, 0, length - 1);

    return 0;
}

static int read_line(char **line, size_t *length)
{
    if (line == NULL || length == NULL) {
        return -1;
    }

    size_t capacity = 128;
    size_t used = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\0') {
            free(buffer);
            return -1;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 0;
}

static int parse_positions(const char *input, size_t *positions)
{
    if (input == NULL || positions == NULL || input[0] == '\0' ||
        input[0] == '-') {
        return -1;
    }

    size_t value = 0;

    for (size_t i = 0; input[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)input[i];

        if (ch < '0' || ch > '9') {
            return -1;
        }

        size_t digit = (size_t)(ch - '0');

        if (value > (SIZE_MAX - digit) / 10) {
            return -1;
        }

        value = value * 10 + digit;
    }

    *positions = value;
    return 0;
}

int main(void)
{
    char *string = NULL;
    char *input = NULL;
    size_t string_length = 0;
    size_t input_length = 0;
    size_t positions = 0;
    int status = EXIT_FAILURE;

    if (read_line(&string, &string_length) != 0) {
        fputs("Failed to read the string.\n", stderr);
        goto cleanup;
    }

    if (read_line(&input, &input_length) != 0) {
        fputs("Failed to read the rotation count.\n", stderr);
        goto cleanup;
    }

    if (parse_positions(input, &positions) != 0) {
        fputs("Invalid rotation count.\n", stderr);
        goto cleanup;
    }

    if (left_rotate(string, string_length, positions) != 0) {
        fputs("Failed to rotate the string.\n", stderr);
        goto cleanup;
    }

    if (fputs(string, stdout) == EOF || fputc('\n', stdout) == EOF) {
        fputs("Failed to write the result.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    free(string);
    return status;
}