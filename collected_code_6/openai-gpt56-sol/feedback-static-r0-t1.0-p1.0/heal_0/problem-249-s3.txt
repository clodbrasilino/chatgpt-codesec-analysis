#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int *find_intersection(const int *first, size_t first_count,
                              const int *second, size_t second_count,
                              size_t *result_count)
{
    int *first_copy = NULL;
    int *second_copy = NULL;
    int *result = NULL;
    size_t capacity;
    size_t i = 0;
    size_t j = 0;
    size_t count = 0;

    if (result_count == NULL ||
        (first_count > 0 && first == NULL) ||
        (second_count > 0 && second == NULL)) {
        return NULL;
    }

    *result_count = 0;
    capacity = first_count < second_count ? first_count : second_count;

    if (capacity == 0) {
        return NULL;
    }

    if (first_count > SIZE_MAX / sizeof(*first_copy) ||
        second_count > SIZE_MAX / sizeof(*second_copy) ||
        capacity > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    first_copy = malloc(first_count * sizeof(*first_copy));
    second_copy = malloc(second_count * sizeof(*second_copy));
    result = malloc(capacity * sizeof(*result));

    if (first_copy == NULL || second_copy == NULL || result == NULL) {
        free(first_copy);
        free(second_copy);
        free(result);
        return NULL;
    }

    for (size_t index = 0; index < first_count; ++index) {
        first_copy[index] = first[index];
    }

    for (size_t index = 0; index < second_count; ++index) {
        second_copy[index] = second[index];
    }

    qsort(first_copy, first_count, sizeof(*first_copy), compare_ints);
    qsort(second_copy, second_count, sizeof(*second_copy), compare_ints);

    while (i < first_count && j < second_count) {
        if (first_copy[i] < second_copy[j]) {
            ++i;
        } else if (first_copy[i] > second_copy[j]) {
            ++j;
        } else {
            const int value = first_copy[i];

            result[count++] = value;

            while (i < first_count && first_copy[i] == value) {
                ++i;
            }

            while (j < second_count && second_copy[j] == value) {
                ++j;
            }
        }
    }

    free(first_copy);
    free(second_copy);

    if (count == 0) {
        free(result);
        return NULL;
    }

    *result_count = count;
    return result;
}

int main(void)
{
    const int first[] = {1, 2, 2, 3, 4, 5};
    const int second[] = {2, 2, 4, 6};
    const size_t first_count = sizeof(first) / sizeof(first[0]);
    const size_t second_count = sizeof(second) / sizeof(second[0]);
    size_t result_count = 0;
    int *intersection = find_intersection(first, first_count, second,
                                          second_count, &result_count);

    if (intersection == NULL && result_count != 0) {
        fputs("Failed to find the intersection.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Intersection:");

    for (size_t i = 0; i < result_count; ++i) {
        printf(" %d", intersection[i]);
    }

    putchar('\n');
    free(intersection);

    return EXIT_SUCCESS;
}