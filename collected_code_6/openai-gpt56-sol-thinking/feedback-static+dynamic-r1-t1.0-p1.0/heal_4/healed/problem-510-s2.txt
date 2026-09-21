#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INPUT_BUFFER_SIZE = 4096
};

typedef struct {
    FILE *file;
    bool error;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t available;
} InputStream;

static int read_byte(InputStream *stream)
{
    if (stream == NULL || stream->file == NULL || stream->error) {
        return EOF;
    }

    if (stream->position >= stream->available) {
        stream->available = fread(
            stream->buffer,
            sizeof(stream->buffer[0]),
            sizeof(stream->buffer),
            stream->file);
        stream->position = 0;

        if (ferror(stream->file)) {
            stream->error = true;
            return EOF;
        }

        if (stream->available == 0) {
            return EOF;
        }
    }

    return (int)stream->buffer[stream->position++];
}

static bool read_uintmax_value(InputStream *stream, uintmax_t *result)
{
    uintmax_t value = 0;
    int character;

    if (stream == NULL || stream->file == NULL || result == NULL) {
        return false;
    }

    do {
        character = read_byte(stream);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == '+') {
        character = read_byte(stream);
    }

    if (character == EOF || character < '0' || character > '9') {
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

    if (k > SIZE_MAX) {
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
                if ((uint64_t)product > (k - UINT64_C(1)) / value) {
                    continue;
                }

                new_product = (size_t)((uint64_t)product * value);
            }

            if (!add_uint64(&next_counts[new_product], counts[product])) {
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
        .position = 0,
        .available = 0
    };
    uintmax_t input_length;
    uint64_t k;
    uint64_t *array = NULL;
    uint64_t result;
    size_t length;
    size_t i;

    if (!read_uintmax_value(&stream, &input_length) ||
        !read_uint64_value(&stream, &k)) {
        return EXIT_FAILURE;
    }

    if (input_length > SIZE_MAX) {
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
            free(array);
            return EXIT_FAILURE;
        }
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