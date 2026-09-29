#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || b > UINT64_MAX - a) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int double_u64(uint64_t value, uint64_t *result)
{
    return add_u64(value, value, result);
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    int success = 0;

    if (value == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX) {
                free(line);
                return 0;
            }

            char *replacement = realloc(line, new_capacity);

            if (replacement == NULL) {
                free(line);
                return 0;
            }

            line = replacement;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return 0;
    }

    if (length + 1 > capacity) {
        char *replacement = realloc(line, length + 1);

        if (replacement == NULL) {
            free(line);
            return 0;
        }

        line = replacement;
        capacity = length + 1;
    }

    line[length] = '\0';

    char *start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start != '\0' && *start != '-') {
        errno = 0;
        char *end = NULL;
        uintmax_t parsed = strtoumax(start, &end, 10);

        if (errno != ERANGE && end != start && parsed <= UINT64_MAX) {
            while (isspace((unsigned char)*end)) {
                ++end;
            }

            if (*end == '\0') {
                *value = (uint64_t)parsed;
                success = 1;
            }
        }
    }

    free(line);
    return success;
}

typedef struct {
    uint64_t product;
    uint64_t count;
} State;

static int ensure_capacity(State **states, size_t *capacity, size_t required)
{
    if (states == NULL || capacity == NULL) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
    }

    size_t new_capacity = *capacity == 0 ? 16 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof **states) {
        return 0;
    }

    State *replacement = realloc(*states, new_capacity * sizeof **states);

    if (replacement == NULL) {
        return 0;
    }

    *states = replacement;
    *capacity = new_capacity;
    return 1;
}

static int count_subsequences(const uint64_t *array, size_t length,
                              uint64_t k, uint64_t *output)
{
    State *states = NULL;
    size_t state_count = 0;
    size_t capacity = 0;
    uint64_t zero_free_count = 0;
    uint64_t result = 0;

    if (output == NULL || (length != 0 && array == NULL)) {
        return 0;
    }

    if (length == 0 || k == 0) {
        *output = 0;
        return 1;
    }

    for (size_t i = 0; i < length; ++i) {
        uint64_t value = array[i];

        if (value == 0) {
            if (!double_u64(zero_free_count, &zero_free_count) ||
                !add_u64(result, 1, &result) ||
                !add_u64(result, zero_free_count, &result)) {
                free(states);
                return 0;
            }

            for (size_t j = 0; j < state_count; ++j) {
                if (!double_u64(states[j].count, &states[j].count)) {
                    free(states);
                    return 0;
                }
            }

            continue;
        }

        if (!double_u64(zero_free_count, &zero_free_count) ||
            !add_u64(zero_free_count, 1, &zero_free_count)) {
            free(states);
            return 0;
        }

        size_t old_count = state_count;

        if (value < k) {
            if (!ensure_capacity(&states, &capacity, state_count + 1)) {
                free(states);
                return 0;
            }

            states[state_count].product = value;
            states[state_count].count = 1;
            ++state_count;

            if (!add_u64(result, 1, &result)) {
                free(states);
                return 0;
            }
        }

        for (size_t j = 0; j < old_count; ++j) {
            if (states[j].product <= (k - 1) / value) {
                uint64_t new_product = states[j].product * value;
                size_t existing = SIZE_MAX;

                for (size_t m = old_count; m < state_count; ++m) {
                    if (states[m].product == new_product) {
                        existing = m;
                        break;
                    }
                }

                if (existing != SIZE_MAX) {
                    if (!add_u64(states[existing].count,
                                 states[j].count,
                                 &states[existing].count)) {
                        free(states);
                        return 0;
                    }
                } else {
                    if (!ensure_capacity(&states, &capacity,
                                         state_count + 1)) {
                        free(states);
                        return 0;
                    }

                    states[state_count].product = new_product;
                    states[state_count].count = states[j].count;
                    ++state_count;
                }

                if (!add_u64(result, states[j].count, &result)) {
                    free(states);
                    return 0;
                }
            }
        }
    }

    free(states);
    *output = result;
    return 1;
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

    uint64_t result;

    if (!count_subsequences(array, length, k, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}