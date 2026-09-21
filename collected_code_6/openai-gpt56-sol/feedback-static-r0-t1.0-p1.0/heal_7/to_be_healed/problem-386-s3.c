#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (result == NULL || (str == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        switch (str[i]) {
        case '[':
            if (open_count == SIZE_MAX) {
                return 0;
            }

            ++open_count;

            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return 0;
                }

                swaps += imbalance;
                --imbalance;
            }
            break;

        case ']':
            if (close_count == SIZE_MAX) {
                return 0;
            }

            ++close_count;
            imbalance = close_count > open_count
                      ? close_count - open_count
                      : 0;
            break;

        default:
            return 0;
        }
    }

    if (open_count != close_count) {
        return 0;
    }

    *result = swaps;
    return 1;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data = NULL;
    size_t used = 0;
    size_t capacity = 0;
    int ch = EOF;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity == 0) {
                new_capacity = 256;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(data);
                    return 0;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity <= used) {
                free(data);
                return 0;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used] = (char)(unsigned char)ch;
        ++used;
    }

    if (ch == EOF && ferror(stream)) {
        free(data);
        return 0;
    }

    if (used > 0 && data[used - 1] == '\r') {
        --used;
    }

    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t swaps = 0;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &length)) {
        goto cleanup;
    }

    if (!minimum_swaps(input, length, &swaps)) {
        goto cleanup;
    }

    if (printf("%zu\n", swaps) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}