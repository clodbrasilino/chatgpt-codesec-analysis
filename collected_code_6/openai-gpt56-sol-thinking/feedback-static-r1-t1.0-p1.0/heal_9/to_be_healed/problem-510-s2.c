#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t available;
    bool failed;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    reader->stream = stream;
    reader->position = 0;
    reader->available = 0;
    reader->failed = false;
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL || reader->failed) {
        return EOF;
    }

    if (reader->position == reader->available) {
        reader->available = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            sizeof(reader->buffer),
            reader->stream);
        reader->position = 0;

        if (reader->available == 0) {
            if (ferror(reader->stream) != 0) {
                reader->failed = true;
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

    if (reader == NULL || value == NULL || reader->stream == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF && isspace((unsigned char)character) != 0);

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

    if (character == EOF) {
        if (reader->failed) {
            return false;
        }
    } else if (isspace((unsigned char)character) == 0) {
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

    if ((uintmax_t)k > (uintmax_t)SIZE_MAX) {
        return false;
    }

    states = (size_t)k;

    if (states > SIZE_MAX / sizeof(*counts)) {
        return false;
    }

    counts = calloc(states, sizeof(*counts));
    next_counts = calloc(states, sizeof(*next_counts));

    if (counts == NULL || next_counts == NULL) {
        goto cleanup;
    }

    for (i = 0; i < length; ++i) {
        uint64_t value = array[i];

        for (product = 0; product < states; ++product) {
            next_counts[product] = counts[product];
        }

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
    InputReader reader;
    uintmax_t parsed_length;
    uintmax_t parsed_k;
    uintmax_t parsed_value;
    uint64_t *array = NULL;
    uint64_t result;
    uint64_t k;
    size_t length;
    size_t i;
    int status = EXIT_FAILURE;

    input_reader_init(&reader, stdin);

    if (!read_uintmax_value(&reader, &parsed_length) ||
        !read_uintmax_value(&reader, &parsed_k)) {
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
        if (!read_uintmax_value(&reader, &parsed_value) ||
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