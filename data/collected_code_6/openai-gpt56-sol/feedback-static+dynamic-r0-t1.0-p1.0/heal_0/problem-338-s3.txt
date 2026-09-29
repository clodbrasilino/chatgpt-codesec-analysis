#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int count_substrings(const char *str, uint64_t *result)
{
    uint64_t frequencies[256] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    while (*str != '\0') {
        const unsigned char ch = (unsigned char)*str;

        if (UINT64_MAX - total <= frequencies[ch]) {
            return -1;
        }

        total += frequencies[ch] + 1U;
        ++frequencies[ch];
        ++str;
    }

    *result = total;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    uint64_t count = 0;
    int character;
    int status = EXIT_FAILURE;

    for (;;) {
        character = getchar();

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
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

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            goto cleanup;
        }

        new_input = realloc(input, capacity + 1U);
        if (new_input == NULL) {
            goto cleanup;
        }

        input = new_input;
        capacity += 1U;
    }

    input[length] = '\0';

    if (count_substrings(input, &count) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}