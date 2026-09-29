#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (result == NULL || (str == NULL && length != 0)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
            if (open_count == SIZE_MAX) {
                return -1;
            }

            ++open_count;

            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return -1;
                }

                swaps += imbalance;
                --imbalance;
            }
        } else if (str[i] == ']') {
            if (close_count == SIZE_MAX) {
                return -1;
            }

            ++close_count;

            if (close_count > open_count) {
                imbalance = close_count - open_count;
            }
        } else {
            return -1;
        }
    }

    if (open_count != close_count) {
        return -1;
    }

    *result = swaps;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t swaps;
    int status = EXIT_FAILURE;

    for (;;) {
        char buffer[4096];

        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        size_t chunk_length = 0;
        while (chunk_length < sizeof buffer && buffer[chunk_length] != '\0') {
            if (buffer[chunk_length] == '\n') {
                if (chunk_length > SIZE_MAX - length) {
                    goto cleanup;
                }

                size_t required = length + chunk_length;
                if (required > capacity) {
                    char *new_input = realloc(input, required);
                    if (new_input == NULL && required != 0) {
                        goto cleanup;
                    }
                    input = new_input;
                    capacity = required;
                }

                for (size_t i = 0; i < chunk_length; ++i) {
                    if (buffer[i] != '[' && buffer[i] != ']') {
                        goto cleanup;
                    }
                    input[length + i] = buffer[i];
                }

                length = required;
                goto input_complete;
            }

            ++chunk_length;
        }

        if (chunk_length > SIZE_MAX - length) {
            goto cleanup;
        }

        size_t required = length + chunk_length;
        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 4096 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < chunk_length; ++i) {
            if (buffer[i] != '[' && buffer[i] != ']') {
                goto cleanup;
            }
            input[length + i] = buffer[i];
        }

        length = required;
    }

input_complete:
    if (minimum_swaps(input, length, &swaps) != 0) {
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