#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_size_value(size_t *value)
{
    size_t parsed = 0;
    int c;

    if (value == NULL) {
        return false;
    }

    do {
        c = fgetc(stdin);
    } while (c == ' ' || c == '\t' || c == '\n' ||
             c == '\r' || c == '\f' || c == '\v');

    if (c == '+') {
        c = fgetc(stdin);
    }

    if (c < '0' || c > '9') {
        return false;
    }

    do {
        size_t digit = (size_t)(c - '0');

        if (parsed > (SIZE_MAX - digit) / 10) {
            return false;
        }

        parsed = parsed * 10 + digit;
        c = fgetc(stdin);
    } while (c >= '0' && c <= '9');

    if (c != EOF &&
        c != ' ' && c != '\t' && c != '\n' &&
        c != '\r' && c != '\f' && c != '\v') {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int64_value(int64_t *value)
{
    uint64_t magnitude = 0;
    uint64_t limit;
    bool negative = false;
    int c;

    if (value == NULL) {
        return false;
    }

    do {
        c = fgetc(stdin);
    } while (c == ' ' || c == '\t' || c == '\n' ||
             c == '\r' || c == '\f' || c == '\v');

    if (c == '+' || c == '-') {
        negative = c == '-';
        c = fgetc(stdin);
    }

    if (c < '0' || c > '9') {
        return false;
    }

    limit = negative
                ? (uint64_t)INT64_MAX + UINT64_C(1)
                : (uint64_t)INT64_MAX;

    do {
        uint64_t digit = (uint64_t)(c - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        c = fgetc(stdin);
    } while (c >= '0' && c <= '9');

    if (c != EOF &&
        c != ' ' && c != '\t' && c != '\n' &&
        c != '\r' && c != '\f' && c != '\v') {
        return false;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return true;
}

static bool checked_add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool checked_sub_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return false;
    }

    *result = a - b;
    return true;
}

bool max_sum_bitonic_subsequence(const int64_t *array, size_t length,
                                 int64_t *result)
{
    int64_t *increasing = NULL;
    int64_t *decreasing = NULL;
    int64_t best;
    bool success = false;

    if (result == NULL) {
        return false;
    }

    if (length == 0) {
        *result = 0;
        return true;
    }

    if (array == NULL || length > SIZE_MAX / sizeof(*increasing)) {
        return false;
    }

    increasing = malloc(length * sizeof(*increasing));
    if (increasing == NULL) {
        goto cleanup;
    }

    decreasing = malloc(length * sizeof(*decreasing));
    if (decreasing == NULL) {
        goto cleanup;
    }

    for (size_t i = 0; i < length; ++i) {
        increasing[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            int64_t candidate;

            if (array[j] < array[i]) {
                if (!checked_add_int64(increasing[j], array[i], &candidate)) {
                    goto cleanup;
                }

                if (candidate > increasing[i]) {
                    increasing[i] = candidate;
                }
            }
        }
    }

    for (size_t i = length; i-- > 0;) {
        decreasing[i] = array[i];

        for (size_t j = i + 1; j < length; ++j) {
            int64_t candidate;

            if (array[j] < array[i]) {
                if (!checked_add_int64(array[i], decreasing[j], &candidate)) {
                    goto cleanup;
                }

                if (candidate > decreasing[i]) {
                    decreasing[i] = candidate;
                }
            }
        }
    }

    best = array[0];

    for (size_t i = 0; i < length; ++i) {
        int64_t decreasing_tail;
        int64_t candidate;

        if (!checked_sub_int64(decreasing[i], array[i], &decreasing_tail) ||
            !checked_add_int64(increasing[i], decreasing_tail, &candidate)) {
            goto cleanup;
        }

        if (candidate > best) {
            best = candidate;
        }
    }

    *result = best;
    success = true;

cleanup:
    free(decreasing);
    free(increasing);
    return success;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t result;

    if (!read_size_value(&length)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64_value(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_bitonic_subsequence(array, length, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}