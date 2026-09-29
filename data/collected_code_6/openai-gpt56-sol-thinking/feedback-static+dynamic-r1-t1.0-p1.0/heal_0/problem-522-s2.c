#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    LBS_SUCCESS = 0,
    LBS_INVALID_ARGUMENT = 1,
    LBS_ALLOCATION_FAILURE = 2
};

int find_longest_bitonic_subsequence(const int *array, size_t length,
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
        (array == NULL && length != 0)) {
        return LBS_INVALID_ARGUMENT;
    }

    *subsequence = NULL;
    *subsequence_length = 0;

    if (length == 0) {
        return LBS_SUCCESS;
    }

    if (length > SIZE_MAX / sizeof(*increasing) ||
        length > SIZE_MAX / sizeof(*result)) {
        return LBS_ALLOCATION_FAILURE;
    }

    increasing = malloc(length * sizeof(*increasing));
    decreasing = malloc(length * sizeof(*decreasing));
    previous = malloc(length * sizeof(*previous));
    next = malloc(length * sizeof(*next));

    if (increasing == NULL || decreasing == NULL ||
        previous == NULL || next == NULL) {
        free(increasing);
        free(decreasing);
        free(previous);
        free(next);
        return LBS_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        increasing[i] = 1;
        previous[i] = SIZE_MAX;

        for (size_t j = 0; j < i; ++j) {
            if (array[j] < array[i] &&
                increasing[j] + 1 > increasing[i]) {
                increasing[i] = increasing[j] + 1;
                previous[i] = j;
            }
        }
    }

    for (size_t i = length; i-- > 0;) {
        decreasing[i] = 1;
        next[i] = SIZE_MAX;

        for (size_t j = i + 1; j < length; ++j) {
            if (array[j] < array[i] &&
                decreasing[j] + 1 > decreasing[i]) {
                decreasing[i] = decreasing[j] + 1;
                next[i] = j;
            }
        }
    }

    for (size_t i = 0; i < length; ++i) {
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

    while (position > 0) {
        result[position - 1] = array[index];

        if (position == 1) {
            break;
        }

        index = previous[index];
        --position;
    }

    position = increasing[peak];
    index = next[peak];

    while (index != SIZE_MAX) {
        result[position] = array[index];
        ++position;
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
    size_t length;
    int *array = NULL;
    int *subsequence = NULL;
    size_t subsequence_length = 0;
    int status = EXIT_SUCCESS;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        if (length > SIZE_MAX / sizeof(*array)) {
            return EXIT_FAILURE;
        }

        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (scanf("%d", &array[i]) != 1) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    if (find_longest_bitonic_subsequence(array, length, &subsequence,
                                         &subsequence_length) != LBS_SUCCESS) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", subsequence_length) < 0) {
        status = EXIT_FAILURE;
    }

    for (size_t i = 0; i < subsequence_length && status == EXIT_SUCCESS; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", subsequence[i]) < 0) {
            status = EXIT_FAILURE;
        }
    }

    if (status == EXIT_SUCCESS && putchar('\n') == EOF) {
        status = EXIT_FAILURE;
    }

    free(subsequence);
    free(array);

    return status;
}