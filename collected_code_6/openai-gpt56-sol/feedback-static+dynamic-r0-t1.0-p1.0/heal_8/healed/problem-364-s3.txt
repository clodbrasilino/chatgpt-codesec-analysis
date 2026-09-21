#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        char expected = (i % 2U == 0U) ? '0' : '1';

        if (str[i] != '0' && str[i] != '1') {
            return 0;
        }

        if (str[i] != expected) {
            ++flips_starting_with_zero;
        }
    }

    size_t flips_starting_with_one = length - flips_starting_with_zero;
    *result = flips_starting_with_zero < flips_starting_with_one
                  ? flips_starting_with_zero
                  : flips_starting_with_one;

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t flips = 0;
    int status = EXIT_FAILURE;
    int ch = 0;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (ch != '0' && ch != '1') {
            goto cleanup;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length ||
                new_capacity > SIZE_MAX / sizeof(*input)) {
                goto cleanup;
            }

            resized = realloc(input, new_capacity * sizeof(*input));
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length] = (char)ch;
        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (!minimum_flips(input != NULL ? input : "", length, &flips)) {
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