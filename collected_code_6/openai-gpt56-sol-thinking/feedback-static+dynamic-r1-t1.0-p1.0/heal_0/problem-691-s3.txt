#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int second;
    int *first_elements;
    size_t count;
} Group;

typedef struct {
    Group *groups;
    int *values;
    size_t count;
} GroupedTuples;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    return 0;
}

static void free_grouped_tuples(GroupedTuples *result)
{
    if (result != NULL) {
        free(result->values);
        free(result->groups);
        result->values = NULL;
        result->groups = NULL;
        result->count = 0;
    }
}

static int group_first_elements_by_second(const Tuple *tuples,
                                          size_t tuple_count,
                                          GroupedTuples *result)
{
    Tuple *sorted = NULL;
    Group *groups = NULL;
    int *values = NULL;
    size_t group_count = 0;
    size_t group_index = 0;
    size_t value_index = 0;
    size_t i;

    if (result == NULL || (tuples == NULL && tuple_count != 0)) {
        return -1;
    }

    result->groups = NULL;
    result->values = NULL;
    result->count = 0;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuple_count > SIZE_MAX / sizeof(*sorted) ||
        tuple_count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    sorted = malloc(tuple_count * sizeof(*sorted));
    values = malloc(tuple_count * sizeof(*values));

    if (sorted == NULL || values == NULL) {
        free(sorted);
        free(values);
        return -1;
    }

    for (i = 0; i < tuple_count; ++i) {
        sorted[i] = tuples[i];
    }

    qsort(sorted, tuple_count, sizeof(*sorted), compare_tuples);

    group_count = 1;
    for (i = 1; i < tuple_count; ++i) {
        if (sorted[i].second != sorted[i - 1].second) {
            ++group_count;
        }
    }

    if (group_count > SIZE_MAX / sizeof(*groups)) {
        free(sorted);
        free(values);
        return -1;
    }

    groups = calloc(group_count, sizeof(*groups));
    if (groups == NULL) {
        free(sorted);
        free(values);
        return -1;
    }

    i = 0;
    while (i < tuple_count) {
        size_t start = i;
        int second = sorted[i].second;

        groups[group_index].second = second;
        groups[group_index].first_elements = values + value_index;

        while (i < tuple_count && sorted[i].second == second) {
            values[value_index++] = sorted[i].first;
            ++groups[group_index].count;
            ++i;
        }

        if (i == start) {
            free(sorted);
            free(values);
            free(groups);
            return -1;
        }

        ++group_index;
    }

    free(sorted);
    result->groups = groups;
    result->values = values;
    result->count = group_count;
    return 0;
}

int main(void)
{
    Tuple *tuples = NULL;
    GroupedTuples result = {0};
    size_t tuple_count;
    size_t i;
    size_t j;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &tuple_count) != 1) {
        return EXIT_FAILURE;
    }

    if (tuple_count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    if (tuple_count != 0) {
        tuples = malloc(tuple_count * sizeof(*tuples));
        if (tuples == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < tuple_count; ++i) {
        if (scanf("%d %d", &tuples[i].first, &tuples[i].second) != 2) {
            goto cleanup;
        }
    }

    if (group_first_elements_by_second(tuples, tuple_count, &result) != 0) {
        goto cleanup;
    }

    for (i = 0; i < result.count; ++i) {
        if (printf("%d: [", result.groups[i].second) < 0) {
            goto cleanup;
        }

        for (j = 0; j < result.groups[i].count; ++j) {
            if (printf("%s%d",
                       j == 0 ? "" : ", ",
                       result.groups[i].first_elements[j]) < 0) {
                goto cleanup;
            }
        }

        if (printf("]\n") < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free_grouped_tuples(&result);
    free(tuples);
    return status;
}