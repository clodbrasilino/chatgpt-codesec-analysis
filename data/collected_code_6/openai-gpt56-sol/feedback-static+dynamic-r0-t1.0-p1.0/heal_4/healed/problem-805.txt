#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
    const int64_t *elements;
    size_t length;
} IntList;

typedef enum {
    FIND_MAX_OK,
    FIND_MAX_INVALID_ARGUMENT,
    FIND_MAX_OVERFLOW,
    FIND_MAX_EMPTY
} FindMaxResult;

static int add_int64_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static FindMaxResult find_list_with_highest_sum(
    const IntList *lists,
    size_t list_count,
    size_t *max_index,
    int64_t *max_sum)
{
    size_t best_index = 0;
    int64_t best_sum = 0;

    if (lists == NULL || max_index == NULL || max_sum == NULL) {
        return FIND_MAX_INVALID_ARGUMENT;
    }

    if (list_count == 0) {
        return FIND_MAX_EMPTY;
    }

    for (size_t i = 0; i < list_count; ++i) {
        int64_t sum = 0;

        if (lists[i].length > 0 && lists[i].elements == NULL) {
            return FIND_MAX_INVALID_ARGUMENT;
        }

        for (size_t j = 0; j < lists[i].length; ++j) {
            if (!add_int64_checked(sum, lists[i].elements[j], &sum)) {
                return FIND_MAX_OVERFLOW;
            }
        }

        if (i == 0 || sum > best_sum) {
            best_sum = sum;
            best_index = i;
        }
    }

    *max_index = best_index;
    *max_sum = best_sum;
    return FIND_MAX_OK;
}

int main(void)
{
    static const int64_t first[] = {4, 7, -2};
    static const int64_t second[] = {10, 3, 8};
    static const int64_t third[] = {20, -1, -5};

    static const IntList lists[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]}
    };

    const size_t list_count = sizeof lists / sizeof lists[0];
    size_t max_index;
    int64_t max_sum;

    const FindMaxResult result = find_list_with_highest_sum(
        lists, list_count, &max_index, &max_sum
    );

    if (result != FIND_MAX_OK) {
        if (fputs("Unable to find the list with the highest sum.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (fprintf(stdout, "%s%zu%s", "List ", max_index, ":") < 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < lists[max_index].length; ++i) {
        if (fprintf(stdout, "%s%" PRId64, " ",
                    lists[max_index].elements[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (fprintf(stdout, "%s%" PRId64 "%s", "\nSum: ", max_sum, "\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}