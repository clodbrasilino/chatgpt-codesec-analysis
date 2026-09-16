#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

typedef struct {
    const int64_t *elements;
    size_t length;
} IntList;

bool find_maximum_list_sum(const IntList *lists, size_t list_count, int64_t *maximum_sum)
{
    int64_t current_max = 0;

    if (lists == NULL || maximum_sum == NULL || list_count == 0U) {
        return false;
    }

    for (size_t i = 0U; i < list_count; ++i) {
        int64_t sum = 0;

        if (lists[i].elements == NULL && lists[i].length != 0U) {
            return false;
        }

        for (size_t j = 0U; j < lists[i].length; ++j) {
            int64_t value = lists[i].elements[j];

            if ((value > 0 && sum > INT64_MAX - value) ||
                (value < 0 && sum < INT64_MIN - value)) {
                return false;
            }

            sum += value;
        }

        if (i == 0U || sum > current_max) {
            current_max = sum;
        }
    }

    *maximum_sum = current_max;
    return true;
}

int main(void)
{
    const int64_t first[] = {1, 2, 3};
    const int64_t second[] = {10, -2, 5};
    const int64_t third[] = {-4, -8, -1};
    const IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    int64_t maximum_sum;

    if (!find_maximum_list_sum(
            lists,
            sizeof(lists) / sizeof(lists[0]),
            &maximum_sum)) {
        if (fputs("Unable to calculate the maximum sum.\n", stderr) == EOF) {
            return 2;
        }
        return 1;
    }

    if (printf("Maximum sum: %" PRId64 "\n", maximum_sum) < 0) {
        return 2;
    }

    return 0;
}