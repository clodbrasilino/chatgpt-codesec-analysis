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

        if (frequency == UINT64_MAX || total == UINT64_MAX ||
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

static int read_line(unsigned char **buffer, size_t *length)
{
    unsigned char *data = NULL;
    size_t capacity = 0;
    size_t used = 0;
    int character;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == EOF || character == '\n') {
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            unsigned char *temporary;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(data);
                    return -1;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= used) {
                free(data);
                return -1;
            }

            temporary = realloc(data, new_capacity);
            if (temporary == NULL) {
                free(data);
                return -1;
            }

            data = temporary;
            capacity = new_capacity;
        }

        data[used++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(data);
        return -1;
    }

    if (used == SIZE_MAX) {
        free(data);
        return -1;
    }

    if (capacity <= used) {
        unsigned char *temporary = realloc(data, used + 1U);

        if (temporary == NULL) {
            free(data);
            return -1;
        }

        data = temporary;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    uint64_t count;
    int status = EXIT_FAILURE;

    if (read_line(&input, &length) != 0) {
        goto cleanup;
    }

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