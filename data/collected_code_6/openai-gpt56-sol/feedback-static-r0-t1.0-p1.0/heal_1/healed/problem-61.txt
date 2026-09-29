#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <sys/types.h>

static int count_substrings(const char *digits, size_t length, uint64_t *result)
{
    uint64_t *frequencies;
    size_t table_size;
    size_t offset;
    int64_t prefix = 0;
    uint64_t count = 0;

    if (digits == NULL || result == NULL) {
        return -1;
    }

    if (length > (size_t)INT64_MAX) {
        return -1;
    }

    if (length > (SIZE_MAX - 1U) / 9U) {
        return -1;
    }

    table_size = 9U * length + 1U;
    if (table_size > SIZE_MAX / sizeof(*frequencies)) {
        return -1;
    }

    frequencies = calloc(table_size, sizeof(*frequencies));
    if (frequencies == NULL) {
        return -1;
    }

    offset = length;
    frequencies[offset] = 1U;

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)digits[i];
        int64_t index;

        if (character < (unsigned char)'0' ||
            character > (unsigned char)'9') {
            free(frequencies);
            return -1;
        }

        prefix += (int64_t)(character - (unsigned char)'0') - 1;
        index = prefix + (int64_t)offset;

        if (index < 0 || (uint64_t)index >= (uint64_t)table_size) {
            free(frequencies);
            return -1;
        }

        if (frequencies[(size_t)index] > UINT64_MAX - count) {
            free(frequencies);
            return -1;
        }

        count += frequencies[(size_t)index];

        if (frequencies[(size_t)index] == UINT64_MAX) {
            free(frequencies);
            return -1;
        }

        ++frequencies[(size_t)index];
    }

    free(frequencies);
    *result = count;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length;
    ssize_t input_length;
    uint64_t count;

    input_length = getline(&input, &capacity, stdin);
    if (input_length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    length = (size_t)input_length;

    while (length > 0U &&
           (input[length - 1U] == '\n' || input[length - 1U] == '\r')) {
        --length;
    }

    if (count_substrings(input, length, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (fclose(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}