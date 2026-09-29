#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static int count_substrings(const char *str, uint64_t *result)
{
    uint64_t frequencies[UCHAR_MAX + 1U] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str;

        if (frequencies[ch] == UINT64_MAX ||
            total > UINT64_MAX - frequencies[ch] - 1U) {
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
    uint64_t count;
    int status = EXIT_FAILURE;
    int character;

    while ((character = getchar()) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64U;
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

        input[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (length == SIZE_MAX) {
        goto cleanup;
    }

    if (length + 1U > capacity) {
        char *new_input = realloc(input, length + 1U);

        if (new_input == NULL) {
            goto cleanup;
        }

        input = new_input;
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