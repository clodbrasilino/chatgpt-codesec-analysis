#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const char *digits, uint64_t *result)
{
    uint64_t counts[9] = {0};
    uint64_t total = 0;
    unsigned int prefix = 0;

    if (digits == NULL || result == NULL) {
        return -1;
    }

    counts[0] = 1;

    for (const unsigned char *p = (const unsigned char *)digits;
         *p != '\0';
         ++p) {
        unsigned int digit;

        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return -1;
        }

        digit = (unsigned int)(*p - (unsigned char)'0');
        prefix = (prefix + digit) % 9U;

        if (UINT64_MAX - total < counts[prefix]) {
            return -1;
        }

        total += counts[prefix];

        if (counts[prefix] == UINT64_MAX) {
            return -1;
        }

        ++counts[prefix];
    }

    *result = total;
    return 0;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    uint64_t answer;
    int status = EXIT_FAILURE;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (ch == '\r') {
            continue;
        }

        if (length == SIZE_MAX - 1U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                goto cleanup;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (buffer == NULL) {
        buffer = malloc(1U);
        if (buffer == NULL) {
            goto cleanup;
        }
    }

    buffer[length] = '\0';

    if (count_substrings(buffer, &answer) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", answer) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(buffer);
    return status;
}