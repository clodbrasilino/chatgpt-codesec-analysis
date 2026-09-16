#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int find_largest_divisible_subset(const int *numbers, size_t count,
                                         int **subset, size_t *subset_size)
{
    int *sorted = NULL;
    int *result = NULL;
    size_t *lengths = NULL;
    size_t *parents = NULL;
    size_t largest_index = 0;
    size_t largest_size = 0;

    if (subset == NULL || subset_size == NULL ||
        (numbers == NULL && count != 0)) {
        return 0;
    }

    *subset = NULL;
    *subset_size = 0;

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

        if (lengths[i] > largest_size) {
            largest_size = lengths[i];
            largest_index = i;
        }
    }

    if (largest_size > SIZE_MAX / sizeof(*result)) {
        free(sorted);
        free(lengths);
        free(parents);
        return 0;
    }

    result = malloc(largest_size * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        free(lengths);
        free(parents);
        return 0;
    }

    for (size_t i = largest_size; i > 0; --i) {
        result[i - 1] = sorted[largest_index];
        largest_index = parents[largest_index];
    }

    free(sorted);
    free(lengths);
    free(parents);

    *subset = result;
    *subset_size = largest_size;
    return 1;
}

int main(void)
{
    size_t count;
    int *numbers = NULL;
    int *subset = NULL;
    size_t subset_size = 0;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*numbers)) {
        return EXIT_FAILURE;
    }

    if (count != 0) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < count; ++i) {
            if (scanf("%d", &numbers[i]) != 1) {
                free(numbers);
                return EXIT_FAILURE;
            }
        }
    }

    if (!find_largest_divisible_subset(numbers, count, &subset, &subset_size)) {
        free(numbers);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < subset_size; ++i) {
        if (i != 0 && putchar(' ') == EOF) {
            goto cleanup;
        }
        if (printf("%d", subset[i]) < 0) {
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(subset);
    free(numbers);
    return status;
}