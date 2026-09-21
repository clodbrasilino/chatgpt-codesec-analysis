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

static int read_byte(unsigned char *value)
{
    if (value == NULL) {
        return -1;
    }

    if (fread(value, sizeof(*value), 1U, stdin) == 1U) {
        return 1;
    }

    if (ferror(stdin)) {
        return -1;
    }

    return feof(stdin) ? 0 : -1;
}

static int read_uintmax_value(uintmax_t *result)
{
    unsigned char character;
    uintmax_t value = 0U;
    int status;
    int first = 1;
    int have_digit = 0;
    int invalid = 0;
    int overflow = 0;

    if (result == NULL) {
        return -1;
    }

    do {
        status = read_byte(&character);
    } while (status == 1 && isspace((int)character));

    if (status <= 0) {
        return status;
    }

    for (;;) {
        if (first && character == (unsigned char)'+') {
            first = 0;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            uintmax_t digit =
                (uintmax_t)(character - (unsigned char)'0');

            have_digit = 1;
            first = 0;

            if (!overflow) {
                if (value > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
                    overflow = 1;
                } else {
                    value = value * UINTMAX_C(10) + digit;
                }
            }
        } else {
            invalid = 1;
            first = 0;
        }

        status = read_byte(&character);

        if (status < 0) {
            return -1;
        }

        if (status == 0 || isspace((int)character)) {
            break;
        }
    }

    if (invalid || overflow || !have_digit) {
        return -1;
    }

    *result = value;
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

            if (value == 0U) {
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
    uint64_t *values = NULL;
    uint64_t k;
    uint64_t result;
    uintmax_t input;
    size_t length;
    size_t i;
    CountStatus status;

    if (read_uintmax_value(&input) != 1 ||
        input > (uintmax_t)SIZE_MAX) {
        return EXIT_FAILURE;
    }

    length = (size_t)input;

    if (read_uintmax_value(&input) != 1 ||
        input > (uintmax_t)UINT64_MAX) {
        return EXIT_FAILURE;
    }

    k = (uint64_t)input;

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
        if (read_uintmax_value(&input) != 1 ||
            input > (uintmax_t)UINT64_MAX) {
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (uint64_t)input;
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