#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temporary = *start;
        *start++ = *end;
        *end-- = temporary;
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

    reverse_range(string, string + positions - 1);
    reverse_range(string + positions, string + length - 1);
    reverse_range(string, string + length - 1);

    return 0;
}

static int read_line(char **line, size_t *length)
{
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
        int character = fgetc(stdin);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stdin) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
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

            if (new_capacity <= used + 1) {
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

        buffer[used++] = (char)character;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *string = NULL;
    char *input = NULL;
    char *end = NULL;
    size_t string_length = 0;
    size_t input_length = 0;
    int status = EXIT_FAILURE;

    if (read_line(&string, &string_length) != 0) {
        fputs("Failed to read the string.\n", stderr);
        goto cleanup;
    }

    if (read_line(&input, &input_length) != 0) {
        fputs("Failed to read the rotation count.\n", stderr);
        goto cleanup;
    }

    if (input_length == 0 || input[0] == '-') {
        fputs(input_length == 0
                  ? "Invalid rotation count.\n"
                  : "Rotation count must be nonnegative.\n",
              stderr);
        goto cleanup;
    }

    errno = 0;
    unsigned long long value = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0') {
        fputs("Invalid rotation count.\n", stderr);
        goto cleanup;
    }

    size_t positions = string_length == 0
                           ? 0
                           : (size_t)(value % (unsigned long long)string_length);

    if (left_rotate(string, string_length, positions) != 0) {
        fputs("Failed to rotate the string.\n", stderr);
        goto cleanup;
    }

    if (fwrite(string, 1, string_length, stdout) != string_length ||
        fputc('\n', stdout) == EOF) {
        fputs("Failed to write the result.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    free(string);
    return status;
}