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
            ++open_count;

            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return 0;
                }

                swaps += imbalance;
                --imbalance;
            }
        } else if (str[i] == ']') {
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
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
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

    if (character == EOF && ferror(stdin)) {
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