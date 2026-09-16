#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} IntList;

bool find_highest_sum_list(const IntList *lists, size_t list_count,
                           size_t *result_index, int64_t *result_sum)
{
    if (lists == NULL || list_count == 0 ||
        result_index == NULL || result_sum == NULL) {
        return false;
    }

    bool found = false;
    size_t highest_index = 0;
    int64_t highest_sum = 0;

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length > 0 && lists[i].elements == NULL) {
            return false;
        }

        int64_t sum = 0;

        for (size_t j = 0; j < lists[i].length; ++j) {
            int64_t value = lists[i].elements[j];

            if ((value > 0 && sum > INT64_MAX - value) ||
                (value < 0 && sum < INT64_MIN - value)) {
                return false;
            }

            sum += value;
        }

        if (!found || sum > highest_sum) {
            highest_sum = sum;
            highest_index = i;
            found = true;
        }
    }

    *result_index = highest_index;
    *result_sum = highest_sum;
    return true;
}

int main(void)
{
    static const int first[] = {3, 5, -2, 8};
    static const int second[] = {10, 12, 4};
    static const int third[] = {7, 1, 2, 3, 4};

    static const IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    size_t result_index;
    int64_t result_sum;

    if (!find_highest_sum_list(
            lists,
            sizeof(lists) / sizeof(lists[0]),
            &result_index,
            &result_sum)) {
        fputs("Unable to find the list with the highest sum.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("List with highest sum: [");

    for (size_t i = 0; i < lists[result_index].length; ++i) {
        printf("%s%d", i == 0 ? "" : ", ", lists[result_index].elements[i]);
    }

    printf("]\nSum: %" PRId64 "\n", result_sum);

    return EXIT_SUCCESS;
}