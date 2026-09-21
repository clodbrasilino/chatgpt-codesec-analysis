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

static int append_character(char **input, size_t *length, size_t *capacity,
                            char character)
{
    if (input == NULL || length == NULL || capacity == NULL) {
        return -1;
    }

    if (*length == SIZE_MAX) {
        return -1;
    }

    if (*length == *capacity) {
        size_t new_capacity;

        if (*capacity == 0) {
            new_capacity = 256;
        } else if (*capacity > SIZE_MAX / 2) {
            new_capacity = SIZE_MAX;
        } else {
            new_capacity = *capacity * 2;
        }

        if (new_capacity <= *length) {
            return -1;
        }

        char *new_input = realloc(*input, new_capacity);
        if (new_input == NULL) {
            return -1;
        }

        *input = new_input;
        *capacity = new_capacity;
    }

    (*input)[*length] = character;
    ++*length;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t swaps = 0;
    int status = EXIT_FAILURE;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    goto cleanup;
                }
            } else if (next == EOF && ferror(stdin)) {
                goto cleanup;
            }

            break;
        }

        if (character != '[' && character != ']') {
            goto cleanup;
        }

        if (append_character(&input, &length, &capacity,
                             (char)character) != 0) {
            goto cleanup;
        }
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

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