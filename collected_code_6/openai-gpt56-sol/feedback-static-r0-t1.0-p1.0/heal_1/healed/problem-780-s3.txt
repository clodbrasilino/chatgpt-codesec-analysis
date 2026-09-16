#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

typedef struct {
    size_t *indices;
    size_t count;
} Combination;

static void free_combinations(Combination *combinations, size_t count)
{
    if (combinations == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(combinations[i].indices);
    }

    free(combinations);
}

static bool append_combination(
    Combination **combinations,
    size_t *count,
    size_t *capacity,
    const size_t *indices,
    size_t index_count)
{
    if (*count == *capacity) {
        size_t new_capacity = (*capacity == 0U) ? 8U : *capacity * 2U;

        if (new_capacity < *capacity ||
            new_capacity > SIZE_MAX / sizeof(**combinations)) {
            return false;
        }

        Combination *resized = realloc(
            *combinations,
            new_capacity * sizeof(**combinations));

        if (resized == NULL) {
            return false;
        }

        *combinations = resized;
        *capacity = new_capacity;
    }

    size_t *copy = NULL;

    if (index_count > 0U) {
        if (index_count > SIZE_MAX / sizeof(*copy)) {
            return false;
        }

        copy = malloc(index_count * sizeof(*copy));
        if (copy == NULL) {
            return false;
        }

        for (size_t i = 0; i < index_count; ++i) {
            copy[i] = indices[i];
        }
    }

    (*combinations)[*count].indices = copy;
    (*combinations)[*count].count = index_count;
    ++(*count);

    return true;
}

static bool search_combinations(
    const long long *tuple_sums,
    size_t tuple_count,
    size_t position,
    long long current_sum,
    long long target_sum,
    size_t *selected,
    size_t selected_count,
    Combination **results,
    size_t *result_count,
    size_t *result_capacity)
{
    if (position == tuple_count) {
        if (selected_count > 0U && current_sum == target_sum) {
            return append_combination(
                results,
                result_count,
                result_capacity,
                selected,
                selected_count);
        }

        return true;
    }

    if (!search_combinations(
            tuple_sums,
            tuple_count,
            position + 1U,
            current_sum,
            target_sum,
            selected,
            selected_count,
            results,
            result_count,
            result_capacity)) {
        return false;
    }

    if ((tuple_sums[position] > 0 &&
         current_sum > LLONG_MAX - tuple_sums[position]) ||
        (tuple_sums[position] < 0 &&
         current_sum < LLONG_MIN - tuple_sums[position])) {
        return true;
    }

    selected[selected_count] = position;

    return search_combinations(
        tuple_sums,
        tuple_count,
        position + 1U,
        current_sum + tuple_sums[position],
        target_sum,
        selected,
        selected_count + 1U,
        results,
        result_count,
        result_capacity);
}

static bool find_sum_combinations(
    const Tuple *tuples,
    size_t tuple_count,
    long long target_sum,
    Combination **results,
    size_t *result_count)
{
    if (results == NULL || result_count == NULL ||
        (tuple_count > 0U && tuples == NULL)) {
        return false;
    }

    *results = NULL;
    *result_count = 0U;

    if (tuple_count == 0U) {
        return true;
    }

    if (tuple_count > SIZE_MAX / sizeof(long long) ||
        tuple_count > SIZE_MAX / sizeof(size_t)) {
        return false;
    }

    long long *tuple_sums = malloc(tuple_count * sizeof(*tuple_sums));
    size_t *selected = malloc(tuple_count * sizeof(*selected));

    if (tuple_sums == NULL || selected == NULL) {
        free(tuple_sums);
        free(selected);
        return false;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].length > 0U && tuples[i].values == NULL) {
            free(tuple_sums);
            free(selected);
            return false;
        }

        long long sum = 0;

        for (size_t j = 0; j < tuples[i].length; ++j) {
            long long value = tuples[i].values[j];

            if ((value > 0 && sum > LLONG_MAX - value) ||
                (value < 0 && sum < LLONG_MIN - value)) {
                free(tuple_sums);
                free(selected);
                return false;
            }

            sum += value;
        }

        tuple_sums[i] = sum;
    }

    size_t capacity = 0U;

    bool success = search_combinations(
        tuple_sums,
        tuple_count,
        0U,
        0,
        target_sum,
        selected,
        0U,
        results,
        result_count,
        &capacity);

    free(tuple_sums);
    free(selected);

    if (!success) {
        free_combinations(*results, *result_count);
        *results = NULL;
        *result_count = 0U;
    }

    return success;
}

static void print_combination(
    const Tuple *tuples,
    const Combination *combination)
{
    printf("[");

    for (size_t i = 0; i < combination->count; ++i) {
        const Tuple *tuple = &tuples[combination->indices[i]];

        if (i > 0U) {
            printf(", ");
        }

        printf("(");

        for (size_t j = 0; j < tuple->length; ++j) {
            if (j > 0U) {
                printf(", ");
            }

            printf("%d", tuple->values[j]);
        }

        printf(")");
    }

    printf("]\n");
}

int main(void)
{
    int values0[] = {1, 2};
    int values1[] = {3, 4};
    int values2[] = {5, -1};
    int values3[] = {2, 2, 2};

    Tuple tuples[] = {
        {values0, sizeof(values0) / sizeof(values0[0])},
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])}
    };

    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    const long long target_sum = 10;
    Combination *results = NULL;
    size_t result_count = 0U;

    if (!find_sum_combinations(
            tuples,
            tuple_count,
            target_sum,
            &results,
            &result_count)) {
        fprintf(stderr, "Unable to find combinations.\n");
        return EXIT_FAILURE;
    }

    printf("Combinations whose tuple sums equal %lld:\n", target_sum);

    for (size_t i = 0; i < result_count; ++i) {
        print_combination(tuples, &results[i]);
    }

    if (result_count == 0U) {
        printf("None\n");
    }

    free_combinations(results, result_count);
    return EXIT_SUCCESS;
}