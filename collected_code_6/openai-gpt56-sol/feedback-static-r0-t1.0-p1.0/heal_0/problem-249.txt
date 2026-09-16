#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int find_intersection(const int *first, size_t first_size,
                             const int *second, size_t second_size,
                             int **result, size_t *result_size)
{
    int *first_copy = NULL;
    int *second_copy = NULL;
    int *intersection = NULL;
    size_t capacity;
    size_t i = 0;
    size_t j = 0;
    size_t count = 0;

    if (result == NULL || result_size == NULL ||
        (first == NULL && first_size != 0) ||
        (second == NULL && second_size != 0)) {
        return -1;
    }

    *result = NULL;
    *result_size = 0;

    if (first_size == 0 || second_size == 0) {
        return 0;
    }

    if (first_size > SIZE_MAX / sizeof(*first_copy) ||
        second_size > SIZE_MAX / sizeof(*second_copy)) {
        return -1;
    }

    first_copy = malloc(first_size * sizeof(*first_copy));
    second_copy = malloc(second_size * sizeof(*second_copy));

    if (first_copy == NULL || second_copy == NULL) {
        free(first_copy);
        free(second_copy);
        return -1;
    }

    for (i = 0; i < first_size; ++i) {
        first_copy[i] = first[i];
    }

    for (i = 0; i < second_size; ++i) {
        second_copy[i] = second[i];
    }

    qsort(first_copy, first_size, sizeof(*first_copy), compare_ints);
    qsort(second_copy, second_size, sizeof(*second_copy), compare_ints);

    capacity = first_size < second_size ? first_size : second_size;

    if (capacity > SIZE_MAX / sizeof(*intersection)) {
        free(first_copy);
        free(second_copy);
        return -1;
    }

    intersection = malloc(capacity * sizeof(*intersection));

    if (intersection == NULL) {
        free(first_copy);
        free(second_copy);
        return -1;
    }

    i = 0;
    while (i < first_size && j < second_size) {
        if (first_copy[i] < second_copy[j]) {
            ++i;
        } else if (first_copy[i] > second_copy[j]) {
            ++j;
        } else {
            intersection[count++] = first_copy[i];

            while (i < first_size && first_copy[i] == intersection[count - 1]) {
                ++i;
            }

            while (j < second_size && second_copy[j] == intersection[count - 1]) {
                ++j;
            }
        }
    }

    free(first_copy);
    free(second_copy);

    if (count == 0) {
        free(intersection);
        intersection = NULL;
    } else {
        int *smaller = realloc(intersection, count * sizeof(*intersection));

        if (smaller != NULL) {
            intersection = smaller;
        }
    }

    *result = intersection;
    *result_size = count;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 2, 3, 4, 5};
    const int second[] = {2, 2, 4, 6};
    int *intersection = NULL;
    size_t intersection_size = 0;
    size_t i;

    if (find_intersection(first, sizeof(first) / sizeof(first[0]),
                          second, sizeof(second) / sizeof(second[0]),
                          &intersection, &intersection_size) != 0) {
        fputs("Failed to find intersection.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < intersection_size; ++i) {
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