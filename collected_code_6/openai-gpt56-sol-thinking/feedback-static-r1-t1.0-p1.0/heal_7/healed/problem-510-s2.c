#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_uintmax_value(FILE *stream, uintmax_t *value)
{
    uintmax_t parsed = 0;
    int character;

    if (stream == NULL || value == NULL) {
        return false;
    }

    do {
        character = fgetc(stream);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF || character < '0' || character > '9') {
        return false;
    }

    do {
        unsigned int digit = (unsigned int)(character - '0');

        if (parsed > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
            return false;
        }

        parsed = parsed * UINTMAX_C(10) + digit;
        character = fgetc(stream);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (ferror(stream) != 0) {
            return false;
        }
    } else if (!isspace((unsigned char)character)) {
        return false;
    }

    *value = parsed;
    return true;
}

bool count_subsequences_product_less_than_k(
    const uint64_t *array,
    size_t length,
    uint64_t k,
    uint64_t *result)
{
    uint64_t *counts = NULL;
    uint64_t *next_counts = NULL;
    uint64_t total = 0;
    size_t allocation_size;
    size_t states;
    size_t i;
    size_t product;
    bool success = false;

    if (result == NULL || (array == NULL && length != 0)) {
        return false;
    }

    *result = 0;

    if (k == 0 || length == 0) {
        return true;
    }

    if (k > (uint64_t)SIZE_MAX) {
        return false;
    }

    states = (size_t)k;

    if (states > SIZE_MAX / sizeof(*counts)) {
        return false;
    }

    allocation_size = states * sizeof(*counts);
    counts = calloc(states, sizeof(*counts));
    next_counts = calloc(states, sizeof(*next_counts));

    if (counts == NULL || next_counts == NULL) {
        goto cleanup;
    }

    for (i = 0; i < length; ++i) {
        uint64_t value = array[i];

        memcpy(next_counts, counts, allocation_size);

        if (value < k) {
            size_t index = (size_t)value;

            if (next_counts[index] == UINT64_MAX) {
                goto cleanup;
            }

            ++next_counts[index];
        }

        for (product = 0; product < states; ++product) {
            size_t new_product;

            if (counts[product] == 0) {
                continue;
            }

            if (value == 0) {
                new_product = 0;
            } else {
                if ((uint64_t)product > (k - UINT64_C(1)) / value) {
                    continue;
                }

                new_product = (size_t)((uint64_t)product * value);
            }

            if (next_counts[new_product] >
                UINT64_MAX - counts[product]) {
                goto cleanup;
            }

            next_counts[new_product] += counts[product];
        }

        {
            uint64_t *temporary = counts;
            counts = next_counts;
            next_counts = temporary;
        }
    }

    for (product = 0; product < states; ++product) {
        if (total > UINT64_MAX - counts[product]) {
            goto cleanup;
        }

        total += counts[product];
    }

    *result = total;
    success = true;

cleanup:
    free(counts);
    free(next_counts);
    return success;
}

int main(void)
{
    uintmax_t parsed_length;
    uintmax_t parsed_k;
    uintmax_t parsed_value;
    uint64_t *array = NULL;
    uint64_t result;
    uint64_t k;
    size_t length;
    size_t i;
    int status = EXIT_FAILURE;

    if (!read_uintmax_value(stdin, &parsed_length) ||
        !read_uintmax_value(stdin, &parsed_k)) {
        goto cleanup;
    }

    if (parsed_length > (uintmax_t)SIZE_MAX ||
        parsed_k > (uintmax_t)UINT64_MAX) {
        goto cleanup;
    }

    length = (size_t)parsed_length;
    k = (uint64_t)parsed_k;

    if (length != 0) {
        if (length > SIZE_MAX / sizeof(*array)) {
            goto cleanup;
        }

        array = malloc(length * sizeof(*array));

        if (array == NULL) {
            goto cleanup;
        }
    }

    for (i = 0; i < length; ++i) {
        if (!read_uintmax_value(stdin, &parsed_value) ||
            parsed_value > (uintmax_t)UINT64_MAX) {
            goto cleanup;
        }

        array[i] = (uint64_t)parsed_value;
    }

    if (!count_subsequences_product_less_than_k(
            array, length, k, &result)) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    return status;
}