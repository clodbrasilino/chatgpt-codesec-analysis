#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int *find_intersection(const int *first, size_t first_size,
                              const int *second, size_t second_size,
                              size_t *result_size)
{
    int *first_copy = NULL;
    int *second_copy = NULL;
    int *result = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t count = 0;
    size_t capacity;

    if (result_size == NULL ||
        (first == NULL && first_size != 0) ||
        (second == NULL && second_size != 0)) {
        return NULL;
    }

    *result_size = 0;
    capacity = first_size < second_size ? first_size : second_size;

    if (first_size > 0) {
        if (first_size > SIZE_MAX / sizeof(*first_copy)) {
            return NULL;
        }

        first_copy = malloc(first_size * sizeof(*first_copy));
        if (first_copy == NULL) {
            return NULL;
        }

        for (i = 0; i < first_size; ++i) {
            first_copy[i] = first[i];
        }

        qsort(first_copy, first_size, sizeof(*first_copy), compare_ints);
    }

    if (second_size > 0) {
        if (second_size > SIZE_MAX / sizeof(*second_copy)) {
            free(first_copy);
            return NULL;
        }

        second_copy = malloc(second_size * sizeof(*second_copy));
        if (second_copy == NULL) {
            free(first_copy);
            return NULL;
        }

        for (i = 0; i < second_size; ++i) {
            second_copy[i] = second[i];
        }

        qsort(second_copy, second_size, sizeof(*second_copy), compare_ints);
    }

    if (capacity > 0) {
        if (capacity > SIZE_MAX / sizeof(*result)) {
            free(second_copy);
            free(first_copy);
            return NULL;
        }

        result = malloc(capacity * sizeof(*result));
        if (result == NULL) {
            free(second_copy);
            free(first_copy);
            return NULL;
        }
    }

    i = 0;

    while (i < first_size && j < second_size) {
        if (first_copy[i] < second_copy[j]) {
            ++i;
        } else if (first_copy[i] > second_copy[j]) {
            ++j;
        } else {
            result[count++] = first_copy[i];

            do {
                ++i;
            } while (i < first_size && first_copy[i] == result[count - 1]);

            do {
                ++j;
            } while (j < second_size && second_copy[j] == result[count - 1]);
        }
    }

    free(second_copy);
    free(first_copy);
    *result_size = count;

    return result;
}

int main(void)
{
    const int first[] = {1, 2, 2, 3, 4, 5};
    const int second[] = {2, 2, 4, 6};
    const size_t first_size = sizeof(first) / sizeof(first[0]);
    const size_t second_size = sizeof(second) / sizeof(second[0]);
    size_t result_size = 0;
    int *intersection = find_intersection(first, first_size, second,
                                          second_size, &result_size);

    if (intersection == NULL && first_size > 0 && second_size > 0) {
        fputs("Failed to compute the intersection.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_size; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", intersection[i]) < 0) {
            free(intersection);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(intersection);
        return EXIT_FAILURE;
    }

    free(intersection);
    return EXIT_SUCCESS;
}