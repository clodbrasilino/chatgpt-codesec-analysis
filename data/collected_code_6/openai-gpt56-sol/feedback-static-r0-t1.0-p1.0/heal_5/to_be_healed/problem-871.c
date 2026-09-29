#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static bool are_rotations(const char *first, size_t first_length,
                          const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    for (size_t offset = 0U; offset < first_length; ++offset) {
        size_t first_index = offset;
        size_t index = 0U;

        while (index < first_length &&
               first[first_index] == second[index]) {
            ++index;
            ++first_index;

            if (first_index == first_length) {
                first_index = 0U;
            }
        }

        if (index == first_length) {
            return true;
        }
    }

    return false;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    const size_t initial_capacity = 128U;
    size_t capacity = initial_capacity;
    size_t used = 0U;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || used == 0U) {
                free(buffer);
                return false;
            }
            break;
        }

        if (used == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return true;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0U;
    size_t second_length = 0U;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &first, &first_length)) {
        goto cleanup;
    }

    if (!read_line(stdin, &second, &second_length)) {
        goto cleanup;
    }

    if (are_rotations(first, first_length, second, second_length)) {
        puts("The strings are rotations of each other.");
    } else {
        puts("The strings are not rotations of each other.");
    }

    status = EXIT_SUCCESS;

cleanup:
    free(first);
    free(second);
    return status;
}