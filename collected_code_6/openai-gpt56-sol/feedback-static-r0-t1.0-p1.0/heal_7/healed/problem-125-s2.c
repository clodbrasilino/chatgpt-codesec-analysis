#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int max_zero_one_difference(const char *string, size_t length,
                                   size_t *start, size_t *end)
{
    int current = 0;
    int maximum = 0;
    size_t current_start = 0;

    if (string == NULL || start == NULL || end == NULL ||
        length > (size_t)INT32_MAX) {
        return -1;
    }

    *start = 0;
    *end = 0;

    for (size_t i = 0; i < length; ++i) {
        int value;

        if (string[i] == '0') {
            value = 1;
        } else if (string[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        if (current < 0) {
            current = value;
            current_start = i;
        } else {
            current += value;
        }

        if (current > maximum) {
            maximum = current;
            *start = current_start;
            *end = i;
        }
    }

    return maximum;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        int character = getchar();

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
            int next = getchar();

            if (next == EOF) {
                if (ferror(stdin)) {
                    goto cleanup;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                goto cleanup;
            }

            break;
        }

        if (character != '0' && character != '1') {
            goto cleanup;
        }

        if (length >= (size_t)INT32_MAX) {
            goto cleanup;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > (size_t)INT32_MAX) {
                new_capacity = (size_t)INT32_MAX;
            }

            if (new_capacity <= capacity ||
                new_capacity > SIZE_MAX / sizeof *input) {
                goto cleanup;
            }

            char *new_input = realloc(input, new_capacity * sizeof *input);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (length == 0) {
        goto cleanup;
    }

    size_t start;
    size_t end;
    int result = max_zero_one_difference(input, length, &start, &end);

    if (result < 0 || printf("%d\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}