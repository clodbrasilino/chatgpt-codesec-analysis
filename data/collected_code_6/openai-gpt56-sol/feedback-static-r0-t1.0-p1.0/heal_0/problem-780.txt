#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int checked_add(long long a, long long b, long long *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > LLONG_MAX - b) ||
        (b < 0 && a < LLONG_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int find_combinations_recursive(
    const Tuple *tuples,
    size_t count,
    size_t index,
    long long target_first,
    long long target_second,
    long long sum_first,
    long long sum_second,
    size_t *selection,
    size_t selection_count,
    size_t *combination_count)
{
    long long next_first;
    long long next_second;
    int status;

    if (tuples == NULL || selection == NULL || combination_count == NULL) {
        return 0;
    }

    if (index == count) {
        if (selection_count > 0 &&
            sum_first == target_first &&
            sum_second == target_second) {
            size_t i;

            printf("{");
            for (i = 0; i < selection_count; ++i) {
                const Tuple tuple = tuples[selection[i]];

                printf("(%d, %d)%s",
                       tuple.first,
                       tuple.second,
                       i + 1 < selection_count ? ", " : "");
            }
            printf("}\n");

            if (*combination_count == SIZE_MAX) {
                return 0;
            }
            ++(*combination_count);
        }

        return 1;
    }

    status = find_combinations_recursive(
        tuples,
        count,
        index + 1,
        target_first,
        target_second,
        sum_first,
        sum_second,
        selection,
        selection_count,
        combination_count);

    if (!status) {
        return 0;
    }

    if (!checked_add(sum_first, tuples[index].first, &next_first) ||
        !checked_add(sum_second, tuples[index].second, &next_second)) {
        return 0;
    }

    selection[selection_count] = index;

    return find_combinations_recursive(
        tuples,
        count,
        index + 1,
        target_first,
        target_second,
        next_first,
        next_second,
        selection,
        selection_count + 1,
        combination_count);
}

static int find_tuple_sum_combinations(
    const Tuple *tuples,
    size_t count,
    long long target_first,
    long long target_second,
    size_t *combination_count)
{
    size_t *selection;
    int status;

    if (combination_count == NULL || (count > 0 && tuples == NULL)) {
        return 0;
    }

    *combination_count = 0;

    if (count == 0) {
        return 1;
    }

    if (count > SIZE_MAX / sizeof(*selection)) {
        return 0;
    }

    selection = malloc(count * sizeof(*selection));
    if (selection == NULL) {
        return 0;
    }

    status = find_combinations_recursive(
        tuples,
        count,
        0,
        target_first,
        target_second,
        0,
        0,
        selection,
        0,
        combination_count);

    free(selection);
    return status;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {2, 3},
        {3, 1},
        {4, 4},
        {-1, 1}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    const long long target_first = 5;
    const long long target_second = 5;
    size_t combination_count;

    errno = 0;

    if (!find_tuple_sum_combinations(
            tuples,
            tuple_count,
            target_first,
            target_second,
            &combination_count)) {
        fprintf(stderr, "Failed to find tuple combinations.\n");
        return EXIT_FAILURE;
    }

    printf("Total combinations: %zu\n", combination_count);

    if (ferror(stdout)) {
        fprintf(stderr, "Output error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}