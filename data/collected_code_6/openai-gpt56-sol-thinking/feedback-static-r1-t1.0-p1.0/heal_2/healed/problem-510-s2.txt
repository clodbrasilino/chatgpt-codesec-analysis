#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool error;
} InputReader;

static int input_reader_get(InputReader *reader)
{
    if (reader->position == reader->length) {
        reader->length = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            sizeof(reader->buffer),
            stdin);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(stdin)) {
                reader->error = true;
            }

            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static bool read_uintmax_value(InputReader *reader, uintmax_t *value)
{
    uintmax_t parsed = 0;
    int character;

    if (reader == NULL || value == NULL || reader->error) {
        return false;
    }

    do {
        character = input_reader_get(reader);
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
        character = input_reader_get(reader);
    } while (character >= '0' && character <= '9');

    if (reader->error) {
        return false;
    }

    if (character != EOF && !isspace((unsigned char)character)) {
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
    uint64_t *counts;
    uint64_t *next_counts;
    uint64_t total = 0;
    size_t states;
    size_t allocation_size;
    size_t i;
    size_t product;

    if (result == NULL || (array == NULL && length != 0)) {
        return false;
    }

    if (k == 0 || length == 0) {
        *result = 0;
        return true;
    }

    if ((uintmax_t)k > (uintmax_t)SIZE_MAX) {
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
        free(counts);
        free(next_counts);
        return false;
    }

    for (i = 0; i < length; ++i) {
        uint64_t value = array[i];

        memcpy(next_counts, counts, allocation_size);

        if (value < k) {
            size_t index = (size_t)value;

            if (next_counts[index] == UINT64_MAX) {
                free(counts);
                free(next_counts);
                return false;
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
                free(counts);
                free(next_counts);
                return false;
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
            free(counts);
            free(next_counts);
            return false;
        }

        total += counts[product];
    }

    free(counts);
    free(next_counts);
    *result = total;
    return true;
}

int main(void)
{
    InputReader reader = {{0}, 0, 0, false};
    uintmax_t parsed_length;
    uintmax_t parsed_k;
    uintmax_t parsed_value;
    uint64_t *array = NULL;
    uint64_t result;
    uint64_t k;
    size_t length;
    size_t i;

    if (!read_uintmax_value(&reader, &parsed_length) ||
        !read_uintmax_value(&reader, &parsed_k)) {
        return EXIT_FAILURE;
    }

    if (parsed_length > (uintmax_t)SIZE_MAX ||
        parsed_k > (uintmax_t)UINT64_MAX) {
        return EXIT_FAILURE;
    }

    length = (size_t)parsed_length;
    k = (uint64_t)parsed_k;

    if (length != 0) {
        if (length > SIZE_MAX / sizeof(*array)) {
            return EXIT_FAILURE;
        }

        array = malloc(length * sizeof(*array));

        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < length; ++i) {
        if (!read_uintmax_value(&reader, &parsed_value) ||
            parsed_value > (uintmax_t)UINT64_MAX) {
            free(array);
            return EXIT_FAILURE;
        }

        array[i] = (uint64_t)parsed_value;
    }

    if (!count_subsequences_product_less_than_k(
            array, length, k, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}