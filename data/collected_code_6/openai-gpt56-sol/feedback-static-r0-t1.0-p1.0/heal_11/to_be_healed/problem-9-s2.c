#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_rotations(const unsigned char *string, size_t length,
                             size_t *result)
{
    size_t *prefix;
    size_t matched = 0;
    size_t period;

    if (result == NULL) {
        return 0;
    }

    if (length == 0) {
        *result = 0;
        return 1;
    }

    if (string == NULL || length > SIZE_MAX / sizeof(*prefix)) {
        return 0;
    }

    prefix = malloc(length * sizeof(*prefix));
    if (prefix == NULL) {
        return 0;
    }

    prefix[0] = 0;

    for (size_t index = 1; index < length; ++index) {
        while (matched > 0 && string[index] != string[matched]) {
            matched = prefix[matched - 1];
        }

        if (string[index] == string[matched]) {
            ++matched;
        }

        prefix[index] = matched;
    }

    period = length - prefix[length - 1];
    *result = (length % period == 0) ? period : length;

    free(prefix);
    return 1;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t rotations;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        unsigned char buffer[4096];
        size_t count;

        if (fgets((char *)buffer, sizeof(buffer), stdin) == NULL) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        count = 0;
        while (count < sizeof(buffer) && buffer[count] != '\0' &&
               buffer[count] != '\n') {
            ++count;
        }

        if (count > SIZE_MAX - length) {
            goto cleanup;
        }

        if (length + count > capacity) {
            size_t required = length + count;
            size_t new_capacity = capacity == 0 ? 64 : capacity;
            unsigned char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        for (size_t index = 0; index < count; ++index) {
            input[length + index] = buffer[index];
        }
        length += count;

        if (count < sizeof(buffer) && buffer[count] == '\n') {
            break;
        }
    }

    if (!minimum_rotations(input, length, &rotations)) {
        goto cleanup;
    }

    if (printf("%zu\n", rotations) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}