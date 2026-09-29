#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t balance = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (result == NULL || (str == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return 0;
                }

                swaps += imbalance;
                --imbalance;
            }

            ++balance;
        } else if (str[i] == ']') {
            if (balance == 0) {
                if (imbalance == SIZE_MAX) {
                    return 0;
                }

                ++imbalance;
            } else {
                --balance;
            }
        } else {
            return 0;
        }
    }

    if (balance != imbalance) {
        return 0;
    }

    *result = swaps;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t swaps = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF || ch == '\n') {
            if (ch == EOF && ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 1024;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (length != 0 && input[length - 1] == '\r') {
        --length;
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