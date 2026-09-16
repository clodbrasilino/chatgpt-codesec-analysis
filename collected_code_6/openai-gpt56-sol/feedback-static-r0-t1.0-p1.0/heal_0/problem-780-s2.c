#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

static bool add_checked(long long a, long long b, long long *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > 0 && a > LLONG_MAX - b) ||
        (b < 0 && a < LLONG_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool print_combinations_recursive(
    const Tuple *tuples,
    size_t tuple_count,
    size_t index,
    long long first_sum,
    long long second_sum,
    long long target_first,
    long long target_second,
    size_t *selected,
    size_t selected_count,
    size_t *match_count)
{
    long long next_first;
    long long next_second;

    if (index == tuple_count) {
        size_t i;

        if (selected_count == 0 ||
            first_sum != target_first ||
            second_sum != target_second) {
            return true;
        }

        if (printf("{") < 0) {
            return false;
        }

        for (i = 0; i < selected_count; ++i) {
            const Tuple tuple = tuples[selected[i]];

            if (printf("%s(%d, %d)",
                       i == 0 ? "" : ", ",
                       tuple.first,
                       tuple.second) < 0) {
                return false;
            }
        }

        if (printf("}\n") < 0) {
            return false;
        }

        ++(*match_count);
        return true;
    }

    if (!print_combinations_recursive(
            tuples,
            tuple_count,
            index + 1,
            first_sum,
            second_sum,
            target_first,
            target_second,
            selected,
            selected_count,
            match_count)) {
        return false;
    }

    if (!add_checked(first_sum, tuples[index].first, &next_first) ||
        !add_checked(second_sum, tuples[index].second, &next_second)) {
        return false;
    }

    selected[selected_count] = index;

    return print_combinations_recursive(
        tuples,
        tuple_count,
        index + 1,
        next_first,
        next_second,
        target_first,
        target_second,
        selected,
        selected_count + 1,
        match_count);
}

static bool find_tuple_sum_combinations(
    const Tuple *tuples,
    size_t tuple_count,
    long long target_first,
    long long target_second,
    size_t *match_count)
{
    size_t *selected;
    bool success;

    if (match_count == NULL || (tuples == NULL && tuple_count != 0)) {
        return false;
    }

    *match_count = 0;

    if (tuple_count == 0) {
        return true;
    }

    if (tuple_count > SIZE_MAX / sizeof(*selected)) {
        return false;
    }

    selected = malloc(tuple_count * sizeof(*selected));
    if (selected == NULL) {
        return false;
    }

    success = print_combinations_recursive(
        tuples,
        tuple_count,
        0,
        0,
        0,
        target_first,
        target_second,
        selected,
        0,
        match_count);

    free(selected);
    return success;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5},
        {-1, 0}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    const long long target_first = 5;
    const long long target_second = 7;
    size_t match_count;

    errno = 0;

    if (!find_tuple_sum_combinations(
            tuples,
            tuple_count,
            target_first,
            target_second,
            &match_count)) {
        if (errno != 0) {
            perror("find_tuple_sum_combinations");
        } else {
            fputs("Unable to find tuple combinations\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("Matches: %zu\n", match_count) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}