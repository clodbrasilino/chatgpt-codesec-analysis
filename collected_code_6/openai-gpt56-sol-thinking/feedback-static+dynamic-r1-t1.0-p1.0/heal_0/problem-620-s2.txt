#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int compare_ints(const void *left, const void *right)
{
    int a = *(const int *)left;
    int b = *(const int *)right;

    return (a > b) - (a < b);
}

int largest_divisible_subset(const int *numbers, size_t count,
                             int **subset, size_t *subset_count)
{
    int *sorted = NULL;
    int *result = NULL;
    size_t *lengths = NULL;
    size_t *parents = NULL;
    size_t best_index = 0;
    size_t best_length = 0;

    if (subset == NULL || subset_count == NULL ||
        (count > 0 && numbers == NULL)) {
        return 0;
    }

    *subset = NULL;
    *subset_count = 0;

    if (count == 0) {
        return 1;
    }

    if (count > SIZE_MAX / sizeof(*sorted) ||
        count > SIZE_MAX / sizeof(*lengths) ||
        count > SIZE_MAX / sizeof(*parents)) {
        return 0;
    }

    sorted = malloc(count * sizeof(*sorted));
    lengths = malloc(count * sizeof(*lengths));
    parents = malloc(count * sizeof(*parents));

    if (sorted == NULL || lengths == NULL || parents == NULL) {
        free(sorted);
        free(lengths);
        free(parents);
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] <= 0) {
            free(sorted);
            free(lengths);
            free(parents);
            return 0;
        }
        sorted[i] = numbers[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ints);

    for (size_t i = 0; i < count; ++i) {
        lengths[i] = 1;
        parents[i] = i;

        for (size_t j = 0; j < i; ++j) {
            if (sorted[i] % sorted[j] == 0 &&
                lengths[j] + 1 > lengths[i]) {
                lengths[i] = lengths[j] + 1;
                parents[i] = j;
            }
        }

        if (lengths[i] > best_length) {
            best_length = lengths[i];
            best_index = i;
        }
    }

    if (best_length > SIZE_MAX / sizeof(*result)) {
        free(sorted);
        free(lengths);
        free(parents);
        return 0;
    }

    result = malloc(best_length * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        free(lengths);
        free(parents);
        return 0;
    }

    size_t index = best_index;
    for (size_t i = best_length; i > 0; --i) {
        result[i - 1] = sorted[index];
        index = parents[index];
    }

    free(sorted);
    free(lengths);
    free(parents);

    *subset = result;
    *subset_count = best_length;
    return 1;
}

int main(void)
{
    size_t count;
    int *numbers = NULL;
    int *subset = NULL;
    size_t subset_count = 0;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*numbers)) {
        return EXIT_FAILURE;
    }

    if (count > 0) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1 || numbers[i] <= 0) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (!largest_divisible_subset(numbers, count, &subset, &subset_count)) {
        free(numbers);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < subset_count; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", subset[i]) < 0) {
            free(numbers);
            free(subset);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(numbers);
        free(subset);
        return EXIT_FAILURE;
    }

    free(numbers);
    free(subset);
    return EXIT_SUCCESS;
}