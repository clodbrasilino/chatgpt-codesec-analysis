#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static int count_substrings(const unsigned char *str, uint64_t *result)
{
    uint64_t frequencies[UCHAR_MAX + 1U] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    while (*str != '\0') {
        uint64_t frequency = frequencies[*str];

        if (frequency == UINT64_MAX ||
            total == UINT64_MAX ||
            frequency > UINT64_MAX - total - UINT64_C(1)) {
            return -1;
        }

        total += frequency + UINT64_C(1);
        frequencies[*str] = frequency + UINT64_C(1);
        ++str;
    }

    *result = total;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    uint64_t count;
    int status = EXIT_FAILURE;
    int character;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > (SIZE_MAX - 1U) / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
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

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (length == SIZE_MAX) {
        goto cleanup;
    }

    if (capacity <= length) {
        unsigned char *new_input = realloc(input, length + 1U);

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