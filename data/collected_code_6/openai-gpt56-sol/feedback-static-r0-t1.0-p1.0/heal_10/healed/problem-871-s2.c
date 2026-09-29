#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define INPUT_CAPACITY 1024U

static bool read_line(char **line, size_t *length)
{
    char *buffer;
    size_t capacity = INPUT_CAPACITY;
    size_t used = 0U;

    if (line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || used == 0U) {
                free(buffer);
                return false;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    free(buffer);
                    return false;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                free(buffer);
                return false;
            }

            break;
        }

        if (used >= capacity - 1U) {
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

        buffer[used++] = (char)(unsigned char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

static bool are_rotations(const char *first, size_t first_length,
                          const char *second, size_t second_length)
{
    size_t start;

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    for (start = 0U; start < first_length; ++start) {
        size_t offset;

        for (offset = 0U; offset < first_length; ++offset) {
            size_t remaining = first_length - start;
            size_t index = offset < remaining
                               ? start + offset
                               : offset - remaining;

            if ((unsigned char)first[index] !=
                (unsigned char)second[offset]) {
                break;
            }
        }

        if (offset == first_length) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0U;
    size_t second_length = 0U;
    int status = EXIT_FAILURE;

    if (!read_line(&first, &first_length)) {
        goto cleanup;
    }

    if (!read_line(&second, &second_length)) {
        goto cleanup;
    }

    if (puts(are_rotations(first, first_length, second, second_length)
                 ? "Yes"
                 : "No") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(first);
    free(second);
    return status;
}