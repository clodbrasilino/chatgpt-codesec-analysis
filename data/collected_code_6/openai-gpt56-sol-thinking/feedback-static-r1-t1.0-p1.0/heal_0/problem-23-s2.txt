#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} IntList;

typedef enum {
    MAX_SUM_SUCCESS,
    MAX_SUM_INVALID_ARGUMENT,
    MAX_SUM_OVERFLOW
} MaxSumStatus;

static MaxSumStatus find_max_list_sum(const IntList *lists,
                                      size_t list_count,
                                      int64_t *maximum_sum)
{
    int64_t maximum = INT64_MIN;

    if (lists == NULL || list_count == 0 || maximum_sum == NULL) {
        return MAX_SUM_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < list_count; ++i) {
        int64_t sum = 0;

        if (lists[i].elements == NULL && lists[i].length != 0) {
            return MAX_SUM_INVALID_ARGUMENT;
        }

        for (size_t j = 0; j < lists[i].length; ++j) {
            int64_t value = lists[i].elements[j];

            if ((value > 0 && sum > INT64_MAX - value) ||
                (value < 0 && sum < INT64_MIN - value)) {
                return MAX_SUM_OVERFLOW;
            }

            sum += value;
        }

        if (sum > maximum) {
            maximum = sum;
        }
    }

    *maximum_sum = maximum;
    return MAX_SUM_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {-5, 10, 7};
    const int third[] = {4, 5, 6};

    const IntList lists[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]}
    };

    int64_t maximum_sum;
    MaxSumStatus status = find_max_list_sum(
        lists,
        sizeof lists / sizeof lists[0],
        &maximum_sum
    );

    if (status == MAX_SUM_INVALID_ARGUMENT) {
        if (fprintf(stderr, "Invalid argument\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (status == MAX_SUM_OVERFLOW) {
        if (fprintf(stderr, "Integer overflow\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum sum: %" PRId64 "\n", maximum_sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}