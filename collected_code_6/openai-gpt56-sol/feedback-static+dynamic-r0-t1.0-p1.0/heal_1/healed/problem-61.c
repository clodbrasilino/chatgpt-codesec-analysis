#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>

static int count_substrings(const char *digits, size_t length, uint64_t *result)
{
    size_t table_size;
    uint64_t *frequencies;
    int64_t prefix = 0;
    int64_t offset;
    uint64_t count = 0;

    if (digits == NULL || result == NULL) {
        return -1;
    }

    if (length > (size_t)INT64_MAX || length > (SIZE_MAX - 1U) / 9U) {
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

    offset = (int64_t)length;
    frequencies[(size_t)offset] = 1U;

    for (size_t i = 0; i < length; ++i) {
        size_t index;
        unsigned int digit;

        if (digits[i] < '0' || digits[i] > '9') {
            free(frequencies);
            return -1;
        }

        digit = (unsigned int)(digits[i] - '0');
        prefix += (int64_t)digit - 1;
        index = (size_t)(prefix + offset);

        if (frequencies[index] > UINT64_MAX - count) {
            free(frequencies);
            return -1;
        }

        count += frequencies[index];

        if (frequencies[index] == UINT64_MAX) {
            free(frequencies);
            return -1;
        }

        ++frequencies[index];
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

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
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
    return EXIT_SUCCESS;
}