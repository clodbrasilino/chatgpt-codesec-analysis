#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum LbsStatus {
    LBS_SUCCESS,
    LBS_INVALID_ARGUMENT,
    LBS_SIZE_ERROR,
    LBS_ALLOCATION_FAILURE
};

static enum LbsStatus longest_bitonic_subsequence(
    const int *values,
    size_t count,
    int **subsequence,
    size_t *subsequence_length)
{
    size_t *increasing = NULL;
    size_t *decreasing = NULL;
    size_t *previous = NULL;
    size_t *next = NULL;
    int *result = NULL;
    size_t peak = 0;
    size_t best_length = 0;

    if (subsequence == NULL || subsequence_length == NULL ||
        (values == NULL && count != 0)) {
        return LBS_INVALID_ARGUMENT;
    }

    *subsequence = NULL;
    *subsequence_length = 0;

    if (count == 0) {
        return LBS_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(*increasing) ||
        count > SIZE_MAX / sizeof(*result)) {
        return LBS_SIZE_ERROR;
    }

    increasing = malloc(count * sizeof(*increasing));
    decreasing = malloc(count * sizeof(*decreasing));
    previous = malloc(count * sizeof(*previous));
    next = malloc(count * sizeof(*next));

    if (increasing == NULL || decreasing == NULL ||
        previous == NULL || next == NULL) {
        free(increasing);
        free(decreasing);
        free(previous);
        free(next);
        return LBS_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        increasing[i] = 1;
        previous[i] = SIZE_MAX;

        for (size_t j = 0; j < i; ++j) {
            if (values[j] < values[i] &&
                increasing[j] + 1 > increasing[i]) {
                increasing[i] = increasing[j] + 1;
                previous[i] = j;
            }
        }
    }

    for (size_t i = count; i-- > 0;) {
        decreasing[i] = 1;
        next[i] = SIZE_MAX;

        for (size_t j = i + 1; j < count; ++j) {
            if (values[j] < values[i] &&
                decreasing[j] + 1 > decreasing[i]) {
                decreasing[i] = decreasing[j] + 1;
                next[i] = j;
            }
        }
    }

    for (size_t i = 0; i < count; ++i) {
        size_t current_length = increasing[i] + decreasing[i] - 1;

        if (current_length > best_length) {
            best_length = current_length;
            peak = i;
        }
    }

    result = malloc(best_length * sizeof(*result));
    if (result == NULL) {
        free(increasing);
        free(decreasing);
        free(previous);
        free(next);
        return LBS_ALLOCATION_FAILURE;
    }

    size_t position = increasing[peak];
    size_t index = peak;

    while (index != SIZE_MAX) {
        result[--position] = values[index];
        index = previous[index];
    }

    position = increasing[peak];
    index = next[peak];

    while (index != SIZE_MAX) {
        result[position++] = values[index];
        index = next[index];
    }

    free(increasing);
    free(decreasing);
    free(previous);
    free(next);

    *subsequence = result;
    *subsequence_length = best_length;
    return LBS_SUCCESS;
}

int main(void)
{
    size_t count;
    int *values = NULL;
    int *subsequence = NULL;
    size_t subsequence_length = 0;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    enum LbsStatus status = longest_bitonic_subsequence(
        values, count, &subsequence, &subsequence_length);

    free(values);

    if (status != LBS_SUCCESS) {
        if (status == LBS_ALLOCATION_FAILURE) {
            fputs("Memory allocation failed\n", stderr);
        } else if (status == LBS_SIZE_ERROR) {
            fputs("Input size is too large\n", stderr);
        } else {
            fputs("Invalid argument\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", subsequence_length) < 0) {
        free(subsequence);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < subsequence_length; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", subsequence[i]) < 0) {
            free(subsequence);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(subsequence);
        return EXIT_FAILURE;
    }

    free(subsequence);
    return EXIT_SUCCESS;
}