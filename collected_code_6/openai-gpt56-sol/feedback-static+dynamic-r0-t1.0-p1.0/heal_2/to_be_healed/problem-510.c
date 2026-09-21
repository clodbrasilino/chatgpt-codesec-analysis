#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static uint64_t saturating_add(uint64_t a, uint64_t b)
{
    return UINT64_MAX - a < b ? UINT64_MAX : a + b;
}

static uint64_t saturating_double(uint64_t value)
{
    return value > UINT64_MAX / 2 ? UINT64_MAX : value * 2;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return 0;
    }

    errno = 0;
    char *end;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static uint64_t count_subsequences(const uint64_t *array, size_t length,
                                   uint64_t k)
{
    typedef struct {
        uint64_t product;
        uint64_t count;
    } State;

    State *states = NULL;
    size_t state_count = 0;
    size_t capacity = 0;
    uint64_t zero_free_count = 0;
    uint64_t result = 0;

    if (array == NULL || length == 0 || k == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == 0) {
            zero_free_count = saturating_double(zero_free_count);
            result = saturating_add(result, 1);
            result = saturating_add(result, zero_free_count);

            for (size_t j = 0; j < state_count; ++j) {
                states[j].count = saturating_double(states[j].count);
            }

            continue;
        }

        zero_free_count = saturating_add(
            saturating_double(zero_free_count), 1);

        size_t old_count = state_count;

        if (array[i] < k) {
            if (state_count == capacity) {
                size_t new_capacity = capacity == 0 ? 16 : capacity * 2;

                if (new_capacity < capacity ||
                    new_capacity > SIZE_MAX / sizeof *states) {
                    free(states);
                    return UINT64_MAX;
                }

                State *replacement = realloc(
                    states, new_capacity * sizeof *states);

                if (replacement == NULL) {
                    free(states);
                    return UINT64_MAX;
                }

                states = replacement;
                capacity = new_capacity;
            }

            states[state_count].product = array[i];
            states[state_count].count = 1;
            ++state_count;
            result = saturating_add(result, 1);
        }

        for (size_t j = 0; j < old_count; ++j) {
            if (states[j].product <= (k - 1) / array[i]) {
                uint64_t new_product = states[j].product * array[i];
                size_t existing = SIZE_MAX;

                for (size_t m = old_count; m < state_count; ++m) {
                    if (states[m].product == new_product) {
                        existing = m;
                        break;
                    }
                }

                if (existing != SIZE_MAX) {
                    states[existing].count = saturating_add(
                        states[existing].count, states[j].count);
                } else {
                    if (state_count == capacity) {
                        size_t new_capacity =
                            capacity == 0 ? 16 : capacity * 2;

                        if (new_capacity < capacity ||
                            new_capacity > SIZE_MAX / sizeof *states) {
                            free(states);
                            return UINT64_MAX;
                        }

                        State *replacement = realloc(
                            states, new_capacity * sizeof *states);

                        if (replacement == NULL) {
                            free(states);
                            return UINT64_MAX;
                        }

                        states = replacement;
                        capacity = new_capacity;
                    }

                    states[state_count].product = new_product;
                    states[state_count].count = states[j].count;
                    ++state_count;
                }

                result = saturating_add(result, states[j].count);
            }
        }
    }

    free(states);
    return result;
}

int main(void)
{
    uint64_t input_length;
    uint64_t k;

    if (!read_uint64(&input_length) || !read_uint64(&k)) {
        return EXIT_FAILURE;
    }

    if (input_length > SIZE_MAX ||
        input_length > SIZE_MAX / sizeof(uint64_t)) {
        return EXIT_FAILURE;
    }

    size_t length = (size_t)input_length;
    uint64_t *array = NULL;

    if (length != 0) {
        array = malloc(length * sizeof *array);
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_uint64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    uint64_t result = count_subsequences(array, length, k);
    free(array);

    if (result == UINT64_MAX) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}