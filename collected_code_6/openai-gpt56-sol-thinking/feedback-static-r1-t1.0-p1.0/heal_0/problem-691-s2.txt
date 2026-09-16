#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    int key;
    int *values;
    size_t count;
    size_t capacity;
} Group;

typedef struct {
    Group *groups;
    size_t count;
} GroupedResult;

static void free_grouped_result(GroupedResult *result)
{
    if (result == NULL) {
        return;
    }

    for (size_t i = 0; i < result->count; ++i) {
        free(result->groups[i].values);
    }

    free(result->groups);
    result->groups = NULL;
    result->count = 0;
}

static bool group_by_second(const Pair *pairs, size_t pair_count,
                            GroupedResult *result)
{
    if (result == NULL || (pairs == NULL && pair_count != 0)) {
        return false;
    }

    result->groups = NULL;
    result->count = 0;

    if (pair_count == 0) {
        return true;
    }

    if (pair_count > SIZE_MAX / sizeof(*result->groups)) {
        return false;
    }

    result->groups = calloc(pair_count, sizeof(*result->groups));
    if (result->groups == NULL) {
        return false;
    }

    for (size_t i = 0; i < pair_count; ++i) {
        size_t group_index = 0;

        while (group_index < result->count &&
               result->groups[group_index].key != pairs[i].second) {
            ++group_index;
        }

        if (group_index == result->count) {
            result->groups[group_index].key = pairs[i].second;
            result->groups[group_index].capacity = 1;
            ++result->count;
        } else {
            if (result->groups[group_index].capacity == SIZE_MAX) {
                free_grouped_result(result);
                return false;
            }
            ++result->groups[group_index].capacity;
        }
    }

    for (size_t i = 0; i < result->count; ++i) {
        if (result->groups[i].capacity >
            SIZE_MAX / sizeof(*result->groups[i].values)) {
            free_grouped_result(result);
            return false;
        }

        result->groups[i].values =
            malloc(result->groups[i].capacity *
                   sizeof(*result->groups[i].values));

        if (result->groups[i].values == NULL) {
            free_grouped_result(result);
            return false;
        }
    }

    for (size_t i = 0; i < pair_count; ++i) {
        size_t group_index = 0;

        while (group_index < result->count &&
               result->groups[group_index].key != pairs[i].second) {
            ++group_index;
        }

        if (group_index == result->count ||
            result->groups[group_index].count >=
                result->groups[group_index].capacity) {
            free_grouped_result(result);
            return false;
        }

        result->groups[group_index]
            .values[result->groups[group_index].count++] = pairs[i].first;
    }

    return true;
}

static bool print_grouped_result(const GroupedResult *result)
{
    if (result == NULL) {
        return false;
    }

    for (size_t i = 0; i < result->count; ++i) {
        if (printf("%d: [", result->groups[i].key) < 0) {
            return false;
        }

        for (size_t j = 0; j < result->groups[i].count; ++j) {
            if (printf("%s%d", j == 0 ? "" : ", ",
                       result->groups[i].values[j]) < 0) {
                return false;
            }
        }

        if (printf("]\n") < 0) {
            return false;
        }
    }

    return !ferror(stdout);
}

int main(void)
{
    const Pair pairs[] = {
        {1, 5},
        {1, 6},
        {2, 5},
        {2, 6},
        {3, 5}
    };
    GroupedResult result;
    const size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);

    if (!group_by_second(pairs, pair_count, &result)) {
        fprintf(stderr, "Failed to group the tuple list.\n");
        return EXIT_FAILURE;
    }

    if (!print_grouped_result(&result)) {
        fprintf(stderr, "Failed to print the grouped result.\n");
        free_grouped_result(&result);
        return EXIT_FAILURE;
    }

    free_grouped_result(&result);
    return EXIT_SUCCESS;
}