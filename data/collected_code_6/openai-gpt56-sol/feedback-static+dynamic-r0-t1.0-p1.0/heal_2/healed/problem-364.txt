#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;

    if (str == NULL || result == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        char expected = (i % 2 == 0) ? '0' : '1';

        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        if (str[i] != expected) {
            ++flips_starting_with_zero;
        }
    }

    {
        size_t flips_starting_with_one = length - flips_starting_with_zero;
        *result = flips_starting_with_zero < flips_starting_with_one
                    ? flips_starting_with_zero
                    : flips_starting_with_one;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t flips = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        char *resized;

        if (capacity - length < 2) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        if (fgets(input + length, (int)(capacity - length), stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                goto cleanup;
            }
            break;
        }

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
            break;
        }
    }

    if (length == 0) {
        goto cleanup;
    }

    if (minimum_flips(input, length, &flips) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", flips) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}