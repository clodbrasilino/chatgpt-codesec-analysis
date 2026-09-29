#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
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
        } else if (str[i] == ']') {
            if (close_count == SIZE_MAX) {
                return 0;
            }

            ++close_count;
            imbalance = close_count > open_count
                      ? close_count - open_count
                      : 0;
        } else {
            return 0;
        }
    }

    if (open_count != close_count) {
        return 0;
    }

    *result = swaps;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t swaps = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    goto cleanup;
                }
                break;
            }

            if (next == '\n') {
                break;
            }

            if (ungetc(next, stdin) == EOF) {
                goto cleanup;
            }

            goto invalid;
        }

        if (character != '[' && character != ']') {
            goto invalid;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                goto cleanup;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            goto cleanup;
        }
    }

    if (!minimum_swaps(input, length, &swaps)) {
        goto invalid;
    }

    if (printf("%zu\n", swaps) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;
    goto cleanup;

invalid:
    if (fputs("Invalid bracket string\n", stderr) == EOF) {
        goto cleanup;
    }

cleanup:
    free(input);
    return status;
}