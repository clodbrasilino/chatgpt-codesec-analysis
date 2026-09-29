#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->first != b->first) {
        return (a->first > b->first) - (a->first < b->first);
    }

    return (a->second > b->second) - (a->second < b->second);
}

static int set_to_ordered_tuples(const int *set, size_t set_size,
                                 Tuple **tuples, size_t *tuple_count)
{
    int *unique = NULL;
    Tuple *result = NULL;
    size_t unique_count = 0;
    size_t count;
    size_t index = 0;

    if (tuples == NULL || tuple_count == NULL ||
        (set == NULL && set_size != 0)) {
        return EINVAL;
    }

    *tuples = NULL;
    *tuple_count = 0;

    if (set_size == 0) {
        return 0;
    }

    if (set_size > SIZE_MAX / sizeof(*unique)) {
        return EOVERFLOW;
    }

    unique = malloc(set_size * sizeof(*unique));
    if (unique == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < set_size; ++i) {
        unique[i] = set[i];
    }

    qsort(unique, set_size, sizeof(*unique), compare_ints);

    for (size_t i = 0; i < set_size; ++i) {
        if (i == 0 || unique[i] != unique[i - 1]) {
            unique[unique_count++] = unique[i];
        }
    }

    if (unique_count != 0 && unique_count > SIZE_MAX / unique_count) {
        free(unique);
        return EOVERFLOW;
    }

    count = unique_count * unique_count;

    if (count > SIZE_MAX / sizeof(*result)) {
        free(unique);
        return EOVERFLOW;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        free(unique);
        return ENOMEM;
    }

    for (size_t i = 0; i < unique_count; ++i) {
        for (size_t j = 0; j < unique_count; ++j) {
            result[index].first = unique[i];
            result[index].second = unique[j];
            ++index;
        }
    }

    qsort(result, count, sizeof(*result), compare_tuples);

    free(unique);
    *tuples = result;
    *tuple_count = count;
    return 0;
}

int main(void)
{
    int set[] = {4, 1, 3, 2, 3, 1};
    Tuple *tuples = NULL;
    size_t tuple_count = 0;
    int status = set_to_ordered_tuples(
        set, sizeof(set) / sizeof(set[0]), &tuples, &tuple_count);

    if (status != 0) {
        fprintf(stderr, "Conversion failed: %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    free(tuples);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}