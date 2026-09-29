#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *file;
    bool error;
    bool end_of_file;
} InputStream;

static int read_byte(InputStream *stream)
{
    int character;

    if (stream == NULL || stream->file == NULL ||
        stream->error || stream->end_of_file) {
        return EOF;
    }

    character = fgetc(stream->file);

    if (character == EOF) {
        if (ferror(stream->file)) {
            stream->error = true;
        } else {
            stream->end_of_file = true;
        }
    }

    return character;
}

static bool read_uintmax_value(InputStream *stream, uintmax_t *result)
{
    uintmax_t value = 0;
    int character;

    if (stream == NULL || stream->file == NULL ||
        result == NULL || stream->error) {
        return false;
    }

    do {
        character = read_byte(stream);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == '+') {
        character = read_byte(stream);
    }

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        uintmax_t digit = (uintmax_t)(character - '0');

        if (value > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
            return false;
        }

        value = value * UINTMAX_C(10) + digit;
        character = read_byte(stream);
    } while (character >= '0' && character <= '9');

    if (stream->error) {
        return false;
    }

    if (character != EOF && !isspace((unsigned char)character)) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_uint64_value(InputStream *stream, uint64_t *result)
{
    uintmax_t value;

    if (result == NULL ||
        !read_uintmax_value(stream, &value) ||
        value > UINT64_MAX) {
        return false;
    }

    *result = (uint64_t)value;
    return true;
}

static bool add_uint64(uint64_t *destination, uint64_t value)
{
    if (destination == NULL || value > UINT64_MAX - *destination) {
        return false;
    }

    *destination += value;
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
        free(counts);
        free(next_counts);
        return false;
    }

    for (i = 0; i < length; ++i) {
        uint64_t value = array[i];

        for (product = 0; product < states; ++product) {
            next_counts[product] = counts[product];
        }

        if (value < k) {
            size_t index = (size_t)value;

            if (!add_uint64(&next_counts[index], UINT64_C(1))) {
                free(counts);
                free(next_counts);
                return false;
            }
        }

        for (product = 0; product < states; ++product) {
            size_t new_product;

            if (counts[product] == 0) {
                continue;
            }

            if (value == 0) {
                new_product = 0;
            } else {
                uint64_t maximum_product =
                    (k - UINT64_C(1)) / value;

                if ((uint64_t)product > maximum_product) {
                    continue;
                }

                new_product = (size_t)((uint64_t)product * value);
            }

            if (!add_uint64(
                    &next_counts[new_product],
                    counts[product])) {
                free(counts);
                free(next_counts);
                return false;
            }
        }

        {
            uint64_t *temporary = counts;
            counts = next_counts;
            next_counts = temporary;
        }
    }

    for (product = 0; product < states; ++product) {
        if (!add_uint64(&total, counts[product])) {
            free(counts);
            free(next_counts);
            return false;
        }
    }

    free(counts);
    free(next_counts);

    *result = total;
    return true;
}

int main(void)
{
    InputStream stream = {
        .file = stdin,
        .error = false,
        .end_of_file = false
    };
    uintmax_t input_length;
    uint64_t k;
    uint64_t *array = NULL;
    uint64_t result;
    size_t length;
    size_t i;
    int status = EXIT_FAILURE;

    if (!read_uintmax_value(&stream, &input_length) ||
        !read_uint64_value(&stream, &k)) {
        return EXIT_FAILURE;
    }

    if (input_length > (uintmax_t)SIZE_MAX) {
        return EXIT_FAILURE;
    }

    length = (size_t)input_length;

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
        if (!read_uint64_value(&stream, &array[i])) {
            goto cleanup;
        }
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