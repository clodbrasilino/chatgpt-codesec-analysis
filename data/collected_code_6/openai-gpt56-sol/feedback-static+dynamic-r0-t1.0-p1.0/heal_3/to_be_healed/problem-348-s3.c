#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || b > UINT64_MAX - a) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_sizes(size_t *first, size_t *second)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *cursor;
    char *end;
    uintmax_t first_value;
    uintmax_t second_value;

    if (first == NULL || second == NULL ||
        fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    cursor = buffer;
    errno = 0;
    first_value = strtoumax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE || first_value > SIZE_MAX) {
        return 0;
    }

    cursor = end;
    errno = 0;
    second_value = strtoumax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE || second_value > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *first = (size_t)first_value;
    *second = (size_t)second_value;
    return 1;
}

static int read_i64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int count_sequences(const int64_t *values, size_t value_count,
                           size_t length, uint64_t *result)
{
    int64_t min_value = 0;
    int64_t max_value = 0;
    size_t negative_span;
    size_t positive_span;
    size_t range;
    size_t zero_index;
    uint64_t *current;
    uint64_t *next;

    if (values == NULL || value_count == 0 || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (values[i] < min_value) {
            min_value = values[i];
        }
        if (values[i] > max_value) {
            max_value = values[i];
        }
    }

    if (length != 0 &&
        ((min_value < 0 &&
          (uint64_t)(-(min_value + 1)) + UINT64_C(1) >
              (uint64_t)(SIZE_MAX / length)) ||
         (max_value > 0 &&
          (uint64_t)max_value > (uint64_t)(SIZE_MAX / length)))) {
        return 0;
    }

    negative_span =
        min_value < 0
            ? (size_t)((uint64_t)(-(min_value + 1)) + UINT64_C(1)) * length
            : 0;
    positive_span =
        max_value > 0 ? (size_t)(uint64_t)max_value * length : 0;

    if (negative_span > SIZE_MAX - positive_span ||
        negative_span + positive_span == SIZE_MAX) {
        return 0;
    }

    range = negative_span + positive_span + 1;
    zero_index = negative_span;

    if (range > SIZE_MAX / sizeof *current) {
        return 0;
    }

    current = calloc(range, sizeof *current);
    next = calloc(range, sizeof *next);

    if (current == NULL || next == NULL) {
        free(current);
        free(next);
        return 0;
    }

    current[zero_index] = UINT64_C(1);

    for (size_t step = 0; step < length; ++step) {
        for (size_t i = 0; i < range; ++i) {
            next[i] = 0;
        }

        for (size_t index = 0; index < range; ++index) {
            if (current[index] == 0) {
                continue;
            }

            for (size_t j = 0; j < value_count; ++j) {
                size_t next_index;

                if (values[j] >= 0) {
                    uint64_t offset = (uint64_t)values[j];

                    if (offset > (uint64_t)(SIZE_MAX - index)) {
                        continue;
                    }

                    next_index = index + (size_t)offset;

                    if (next_index >= range) {
                        continue;
                    }
                } else {
                    uint64_t offset =
                        (uint64_t)(-(values[j] + 1)) + UINT64_C(1);

                    if (offset > (uint64_t)index) {
                        continue;
                    }

                    next_index = index - (size_t)offset;
                }

                if (!add_u64(next[next_index], current[index],
                             &next[next_index])) {
                    free(current);
                    free(next);
                    return 0;
                }
            }
        }

        {
            uint64_t *temporary = current;
            current = next;
            next = temporary;
        }
    }

    *result = 0;

    for (size_t index = zero_index; index < range; ++index) {
        if (!add_u64(*result, current[index], result)) {
            free(current);
            free(next);
            return 0;
        }
    }

    free(current);
    free(next);
    return 1;
}

int main(void)
{
    size_t value_count;
    size_t length;
    int64_t *values;
    uint64_t result;

    if (!read_sizes(&value_count, &length) ||
        value_count == 0 ||
        value_count > SIZE_MAX / sizeof *values) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(value_count * sizeof *values);

    if (values == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (!read_i64(&values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!count_sequences(values, value_count, length, &result)) {
        fputs("Unable to compute result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}