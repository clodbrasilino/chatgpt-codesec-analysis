#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const char *digits, size_t length, uint64_t *result)
{
    size_t table_size;
    uint64_t *frequencies;
    int64_t prefix = 0;
    uint64_t count = 0;

    if (digits == NULL || result == NULL) {
        return -1;
    }

    if (length > (size_t)INT64_MAX ||
        length > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    table_size = length * 2U + 1U;

    if (table_size > SIZE_MAX / sizeof(*frequencies)) {
        return -1;
    }

    frequencies = calloc(table_size, sizeof(*frequencies));
    if (frequencies == NULL) {
        return -1;
    }

    frequencies[length] = UINT64_C(1);

    for (size_t i = 0; i < length; ++i) {
        unsigned char digit = (unsigned char)digits[i];
        int64_t transformed;
        size_t index;

        if (digit < (unsigned char)'0' || digit > (unsigned char)'9') {
            free(frequencies);
            return -1;
        }

        prefix += (int64_t)(digit - (unsigned char)'0') - INT64_C(1);
        transformed = prefix + (int64_t)length;

        if (transformed < 0 ||
            (uint64_t)transformed >= (uint64_t)table_size) {
            free(frequencies);
            return -1;
        }

        index = (size_t)transformed;

        if (count > UINT64_MAX - frequencies[index]) {
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
    size_t input_length;
    ssize_t line_length;
    uint64_t result;
    int status = EXIT_FAILURE;

    line_length = getline(&input, &capacity, stdin);
    if (line_length < 0) {
        goto cleanup;
    }

    input_length = (size_t)line_length;

    while (input_length > 0U &&
           (input[input_length - 1U] == '\n' ||
            input[input_length - 1U] == '\r')) {
        --input_length;
    }

    if (count_substrings(input, input_length, &result) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}