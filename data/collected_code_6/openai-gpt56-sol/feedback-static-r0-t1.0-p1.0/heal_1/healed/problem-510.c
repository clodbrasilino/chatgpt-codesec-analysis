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

static int read_token(char *buffer, size_t size)
{
    int c;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        c = getchar();
        if (c == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)c));

    do {
        if (length + 1 >= size) {
            while ((c = getchar()) != EOF &&
                   !isspace((unsigned char)c)) {
            }
            return 0;
        }

        buffer[length++] = (char)c;
        c = getchar();
    } while (c != EOF && !isspace((unsigned char)c));

    buffer[length] = '\0';
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_size(size_t *value)
{
    uint64_t parsed;

    if (value == NULL || !read_uint64(&parsed) ||
        parsed > (uint64_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int grow_states(void **states, size_t *capacity, size_t element_size)
{
    size_t new_capacity;
    void *replacement;

    if (states == NULL || capacity == NULL || element_size == 0) {
        return 0;
    }

    if (*capacity == 0) {
        new_capacity = 16;
    } else {
        if (*capacity > SIZE_MAX / 2) {
            return 0;
        }
        new_capacity = *capacity * 2;
    }

    if (new_capacity > SIZE_MAX / element_size) {
        return 0;
    }

    replacement = realloc(*states, new_capacity * element_size);
    if (replacement == NULL) {
        return 0;
    }

    *states = replacement;
    *capacity = new_capacity;
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

        zero_free_count =
            saturating_add(saturating_double(zero_free_count), 1);

        size_t old_count = state_count;

        if (array[i] < k) {
            if (state_count == capacity &&
                !grow_states((void **)&states, &capacity, sizeof(*states))) {
                free(states);
                return UINT64_MAX;
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
                    if (state_count == capacity &&
                        !grow_states((void **)&states, &capacity,
                                     sizeof(*states))) {
                        free(states);
                        return UINT64_MAX;
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
    size_t length;
    uint64_t k;
    uint64_t *array;
    uint64_t result;

    if (!read_size(&length) || !read_uint64(&k)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(uint64_t)) {
        return EXIT_FAILURE;
    }

    array = length == 0 ? NULL : malloc(length * sizeof(*array));
    if (length != 0 && array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_uint64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    result = count_subsequences(array, length, k);
    free(array);

    if (result == UINT64_MAX) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}