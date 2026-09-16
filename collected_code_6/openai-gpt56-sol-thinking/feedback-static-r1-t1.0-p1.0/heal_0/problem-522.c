#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int longest_bitonic_subsequence(const int *array, size_t count,
                                int **subsequence, size_t *subsequence_length)
{
    size_t *increasing = NULL;
    size_t *decreasing = NULL;
    size_t *previous = NULL;
    size_t *next = NULL;
    size_t peak = 0;
    size_t maximum_length = 0;
    int *result = NULL;

    if (subsequence == NULL || subsequence_length == NULL ||
        (array == NULL && count != 0)) {
        return -1;
    }

    *subsequence = NULL;
    *subsequence_length = 0;

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*increasing) ||
        count > SIZE_MAX / sizeof(*result)) {
        return -1;
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
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
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

    for (size_t i = count; i-- > 0;) {
        decreasing[i] = 1;
        next[i] = SIZE_MAX;

        for (size_t j = i + 1; j < count; ++j) {
            if (array[j] < array[i] &&
                decreasing[j] + 1 > decreasing[i]) {
                decreasing[i] = decreasing[j] + 1;
                next[i] = j;
            }
        }
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length = increasing[i] + decreasing[i] - 1;

        if (length > maximum_length) {
            maximum_length = length;
            peak = i;
        }
    }

    result = malloc(maximum_length * sizeof(*result));
    if (result == NULL) {
        free(increasing);
        free(decreasing);
        free(previous);
        free(next);
        return -1;
    }

    size_t position = increasing[peak];
    size_t index = peak;

    while (index != SIZE_MAX) {
        result[--position] = array[index];
        index = previous[index];
    }

    position = increasing[peak];
    index = next[peak];

    while (index != SIZE_MAX) {
        result[position++] = array[index];
        index = next[index];
    }

    free(increasing);
    free(decreasing);
    free(previous);
    free(next);

    *subsequence = result;
    *subsequence_length = maximum_length;

    return 0;
}

int main(void)
{
    const int array[] = {1, 11, 2, 10, 4, 5, 2, 1};
    const size_t count = sizeof(array) / sizeof(array[0]);
    int *subsequence = NULL;
    size_t length = 0;

    if (longest_bitonic_subsequence(array, count,
                                    &subsequence, &length) != 0) {
        if (fprintf(stderr, "Unable to find the subsequence.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Length: %zu\nSubsequence:", length) < 0) {
        free(subsequence);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf(" %d", subsequence[i]) < 0) {
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