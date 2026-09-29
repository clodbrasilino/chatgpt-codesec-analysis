#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    COUNT_SUCCESS = 0,
    COUNT_INVALID_ARGUMENT,
    COUNT_MEMORY_ERROR,
    COUNT_RANGE_ERROR,
    COUNT_OVERFLOW
} CountStatus;

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t available;
} InputReader;

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL) {
        return EOF;
    }

    if (reader->position >= reader->available) {
        reader->available = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            sizeof(reader->buffer),
            reader->stream);
        reader->position = 0U;

        if (reader->available == 0U) {
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int read_bounded_uintmax(
    InputReader *reader,
    uintmax_t limit,
    uintmax_t *result)
{
    uintmax_t value = 0U;
    int character;
    int digit_found = 0;

    if (reader == NULL || result == NULL) {
        return 0;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == '+') {
        character = input_reader_get(reader);
    }

    while (character >= '0' && character <= '9') {
        uintmax_t digit = (uintmax_t)(character - '0');

        digit_found = 1;

        if (digit > limit || value > (limit - digit) / 10U) {
            return 0;
        }

        value = value * 10U + digit;
        character = input_reader_get(reader);
    }

    if (!digit_found) {
        return 0;
    }

    if (character != EOF && !isspace((unsigned char)character)) {
        return 0;
    }

    *result = value;
    return 1;
}

static int read_size_value(InputReader *reader, size_t *result)
{
    uintmax_t value;

    if (result == NULL ||
        !read_bounded_uintmax(reader, (uintmax_t)SIZE_MAX, &value)) {
        return 0;
    }

    *result = (size_t)value;
    return 1;
}

static int read_uint64_value(InputReader *reader, uint64_t *result)
{
    uintmax_t value;

    if (result == NULL ||
        !read_bounded_uintmax(reader, (uintmax_t)UINT64_MAX, &value)) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

CountStatus count_subsequences_product_less_than_k(
    const uint64_t *values,
    size_t length,
    uint64_t k,
    uint64_t *result)
{
    uint64_t *current;
    uint64_t *next;
    uint64_t *temporary;
    size_t state_count;
    size_t i;
    size_t product;
    uint64_t total;

    if (result == NULL || (values == NULL && length != 0U)) {
        return COUNT_INVALID_ARGUMENT;
    }

    *result = 0U;

    if (length == 0U || k == 0U) {
        return COUNT_SUCCESS;
    }

    if (k > (uint64_t)SIZE_MAX) {
        return COUNT_RANGE_ERROR;
    }

    state_count = (size_t)k;

    if (state_count > SIZE_MAX / sizeof(*current)) {
        return COUNT_RANGE_ERROR;
    }

    current = calloc(state_count, sizeof(*current));
    if (current == NULL) {
        return COUNT_MEMORY_ERROR;
    }

    next = calloc(state_count, sizeof(*next));
    if (next == NULL) {
        free(current);
        return COUNT_MEMORY_ERROR;
    }

    for (i = 0U; i < length; ++i) {
        uint64_t value = values[i];

        for (product = 0U; product < state_count; ++product) {
            next[product] = current[product];
        }

        if (value < k) {
            size_t index = (size_t)value;

            if (next[index] == UINT64_MAX) {
                free(next);
                free(current);
                return COUNT_OVERFLOW;
            }

            ++next[index];
        }

        for (product = 0U; product < state_count; ++product) {
            size_t target;

            if (current[product] == 0U) {
                continue;
            }

            if (value != 0U &&
                (uint64_t)product > (k - 1U) / value) {
                continue;
            }

            target = value == 0U
                ? 0U
                : (size_t)((uint64_t)product * value);

            if (UINT64_MAX - next[target] < current[product]) {
                free(next);
                free(current);
                return COUNT_OVERFLOW;
            }

            next[target] += current[product];
        }

        temporary = current;
        current = next;
        next = temporary;
    }

    total = 0U;

    for (product = 0U; product < state_count; ++product) {
        if (UINT64_MAX - total < current[product]) {
            free(next);
            free(current);
            return COUNT_OVERFLOW;
        }

        total += current[product];
    }

    free(next);
    free(current);

    *result = total;
    return COUNT_SUCCESS;
}

int main(void)
{
    InputReader reader = {stdin, {0}, 0U, 0U};
    uint64_t *values = NULL;
    uint64_t k;
    uint64_t result;
    size_t length;
    size_t i;
    CountStatus status;

    if (!read_size_value(&reader, &length) ||
        !read_uint64_value(&reader, &k)) {
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        if (length > SIZE_MAX / sizeof(*values)) {
            return EXIT_FAILURE;
        }

        values = malloc(length * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < length; ++i) {
        if (!read_uint64_value(&reader, &values[i])) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = count_subsequences_product_less_than_k(
        values,
        length,
        k,
        &result);

    free(values);

    if (status != COUNT_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}