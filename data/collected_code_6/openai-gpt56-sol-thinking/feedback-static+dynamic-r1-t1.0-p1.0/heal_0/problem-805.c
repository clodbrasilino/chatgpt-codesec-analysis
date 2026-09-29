#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>

typedef struct {
    const int *elements;
    size_t length;
} IntList;

typedef struct {
    const IntList *lists;
    size_t count;
} IntListCollection;

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_SUM_OVERFLOW
} FindResult;

FindResult find_highest_sum_list(
    const IntListCollection *collection,
    const IntList **highest_list,
    int64_t *highest_sum)
{
    size_t i;
    bool found = false;

    if (highest_list == NULL || highest_sum == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *highest_list = NULL;
    *highest_sum = 0;

    if (collection == NULL ||
        collection->count == 0 ||
        collection->lists == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    for (i = 0; i < collection->count; ++i) {
        const IntList *current = &collection->lists[i];
        int64_t sum = 0;
        size_t j;

        if (current->length > 0 && current->elements == NULL) {
            return FIND_INVALID_ARGUMENT;
        }

        for (j = 0; j < current->length; ++j) {
            int64_t value = current->elements[j];

            if ((value > 0 && sum > INT64_MAX - value) ||
                (value < 0 && sum < INT64_MIN - value)) {
                return FIND_SUM_OVERFLOW;
            }

            sum += value;
        }

        if (!found || sum > *highest_sum) {
            *highest_list = current;
            *highest_sum = sum;
            found = true;
        }
    }

    return FIND_SUCCESS;
}

int main(void)
{
    const int first[] = {3, 5, -2, 7};
    const int second[] = {10, 20, 30};
    const int third[] = {-1, 100, -20, 5};

    const IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    const IntListCollection collection = {
        lists,
        sizeof(lists) / sizeof(lists[0])
    };

    const IntList *highest = NULL;
    int64_t highest_sum = 0;
    FindResult result;
    size_t i;

    result = find_highest_sum_list(
        &collection,
        &highest,
        &highest_sum
    );

    if (result == FIND_INVALID_ARGUMENT) {
        if (fprintf(stderr, "Invalid list collection.\n") < 0) {
            return 2;
        }
        return 1;
    }

    if (result == FIND_SUM_OVERFLOW) {
        if (fprintf(stderr, "A list sum exceeded the supported range.\n") < 0) {
            return 2;
        }
        return 1;
    }

    if (printf("Highest-sum list: [") < 0) {
        return 2;
    }

    for (i = 0; i < highest->length; ++i) {
        if (printf("%s%d", i == 0 ? "" : ", ", highest->elements[i]) < 0) {
            return 2;
        }
    }

    if (printf("]\nSum: %" PRId64 "\n", highest_sum) < 0) {
        return 2;
    }

    return 0;
}