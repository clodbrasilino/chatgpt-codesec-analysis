#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t balance = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (result == NULL || (str == NULL && length != 0)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return -1;
                }
                swaps += imbalance;
                --imbalance;
            }

            if (balance == SIZE_MAX) {
                return -1;
            }
            ++balance;
        } else if (str[i] == ']') {
            if (balance != 0) {
                --balance;
            } else {
                if (imbalance == SIZE_MAX) {
                    return -1;
                }
                ++imbalance;
            }
        } else {
            return -1;
        }
    }

    if (balance != imbalance) {
        return -1;
    }

    *result = swaps;
    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0 || *capacity > SIZE_MAX / 2) {
        return -1;
    }

    new_capacity = *capacity * 2;
    new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_input(char **buffer, size_t *length)
{
    size_t capacity = 256;
    size_t used = 0;
    char *input;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    input = malloc(capacity);
    if (input == NULL) {
        return -1;
    }

    for (;;) {
        int value;

        if (used == capacity && grow_buffer(&input, &capacity) != 0) {
            free(input);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        value = fgetc(stdin);

        if (value == EOF) {
            if (ferror(stdin)) {
                free(input);
                return -1;
            }
            break;
        }

        if (value == '\n') {
            break;
        }

        if (value == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    free(input);
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                free(input);
                return -1;
            }
            break;
        }

        if (value != '[' && value != ']') {
            free(input);
            return -1;
        }

        input[used++] = (char)value;
    }

    *buffer = input;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t swaps = 0;
    int status = EXIT_FAILURE;

    if (read_input(&input, &length) != 0) {
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