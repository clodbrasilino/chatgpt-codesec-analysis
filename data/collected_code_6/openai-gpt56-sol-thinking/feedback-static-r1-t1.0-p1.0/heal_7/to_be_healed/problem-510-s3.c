#include <inttypes.h>
#include <stddef.h>
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
    int error;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader != NULL) {
        reader->stream = stream;
        reader->position = 0U;
        reader->available = 0U;
        reader->error = 0;
    }
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL || reader->error) {
        return EOF;
    }

    if (reader->position == reader->available) {
        reader->position = 0U;
        reader->available = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            sizeof(reader->buffer) / sizeof(reader->buffer[0]),
            reader->stream);

        if (ferror(reader->stream)) {
            reader->available = 0U;
            reader->error = 1;
            return EOF;
        }

        if (reader->available == 0U) {
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int is_input_space(int character)
{
    return character == ' ' ||
           character == '\t' ||
           character == '\n' ||
           character == '\r' ||
           character == '\f' ||
           character == '\v';
}

static int read_bounded_uintmax(
    InputReader *reader,
    uintmax_t limit,
    uintmax_t *result)
{
    uintmax_t value = UINTMAX_C(0);
    int character;
    int digit_found = 0;

    if (reader == NULL ||
        reader->stream == NULL ||
        result == NULL ||
        reader->error) {
        return 0;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF && is_input_space(character));

    if (character == '+') {
        character = input_reader_get(reader);
    }

    while (character >= '0' && character <= '9') {
        uintmax_t digit = (uintmax_t)(character - '0');

        digit_found = 1;

        if (digit > limit ||
            value > (limit - digit) / UINTMAX_C(10)) {
            return 0;
        }

        value = value * UINTMAX_C(10) + digit;
        character = input_reader_get(reader);
    }

    if (!digit_found || reader->error) {
        return 0;
    }

    if (character != EOF && !is_input_space(character)) {
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
    uint64_t *current = NULL;
    uint64_t *next = NULL;
    uint64_t *temporary;
    uint64_t total = UINT64_C(0);
    size_t state_count;
    size_t product;
    size_t i;

    if (result == NULL || (values == NULL && length != 0U)) {
        return COUNT_INVALID_ARGUMENT;
    }

    *result = UINT64_C(0);

    if (length == 0U || k == UINT64_C(0)) {
        return COUNT_SUCCESS;
    }

    if ((uintmax_t)k > (uintmax_t)SIZE_MAX) {
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

    next = malloc(state_count * sizeof(*next));
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

            if (current[product] == UINT64_C(0)) {
                continue;
            }

            if (value == UINT64_C(0)) {
                target = 0U;
            } else {
                if ((uint64_t)product > (k - UINT64_C(1)) / value) {
                    continue;
                }

                target = (size_t)((uint64_t)product * value);
            }

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
    InputReader reader;
    uint64_t *values = NULL;
    uint64_t k;
    uint64_t result;
    size_t length;
    size_t i;
    CountStatus status;

    input_reader_init(&reader, stdin);

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

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}