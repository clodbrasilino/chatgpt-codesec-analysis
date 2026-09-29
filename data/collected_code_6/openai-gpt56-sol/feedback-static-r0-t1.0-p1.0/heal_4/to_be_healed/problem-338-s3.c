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
            frequency > UINT64_MAX - total - 1U) {
            return -1;
        }

        total += frequency + 1U;
        frequencies[*str] = frequency + 1U;
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
    int character;
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *temporary;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                goto cleanup;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (length == SIZE_MAX) {
        goto cleanup;
    }

    if (capacity < length + 1U) {
        unsigned char *temporary = realloc(input, length + 1U);

        if (temporary == NULL) {
            goto cleanup;
        }

        input = temporary;
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