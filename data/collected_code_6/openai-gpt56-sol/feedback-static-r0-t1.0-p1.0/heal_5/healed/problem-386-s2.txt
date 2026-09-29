#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t balance = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        switch (str[i]) {
        case '[':
            if (balance == SIZE_MAX) {
                return 0;
            }

            ++balance;

            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return 0;
                }

                swaps += imbalance;
                --imbalance;
            }
            break;

        case ']':
            if (balance != 0) {
                --balance;
            } else {
                if (imbalance == SIZE_MAX) {
                    return 0;
                }

                ++imbalance;
            }
            break;

        default:
            return 0;
        }
    }

    if (balance != 0 || imbalance != 0) {
        return 0;
    }

    *result = swaps;
    return 1;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data = NULL;
    size_t capacity = 0;
    size_t used = 0;
    int character;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (used == capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity == 0) {
                new_capacity = 64;
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

        data[used++] = (char)character;
    }

    if (character == EOF && ferror(stream)) {
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
    size_t length = 0;
    size_t swaps = 0;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &length)) {
        goto cleanup;
    }

    if (!minimum_swaps(input != NULL ? input : "", length, &swaps)) {
        if (fputs("Invalid bracket string\n", stderr) == EOF) {
            goto cleanup;
        }

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