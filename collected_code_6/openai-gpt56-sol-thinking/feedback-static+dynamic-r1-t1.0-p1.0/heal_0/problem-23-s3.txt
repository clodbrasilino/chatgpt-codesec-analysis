#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUM_STATUS_OK,
    SUM_STATUS_INVALID_ARGUMENT,
    SUM_STATUS_OVERFLOW
} SumStatus;

static bool checked_add(long long left, int right, long long *result)
{
    long long value = (long long)right;

    if ((value > 0 && left > LLONG_MAX - value) ||
        (value < 0 && left < LLONG_MIN - value)) {
        return false;
    }

    *result = left + value;
    return true;
}

static SumStatus find_max_list_sum(
    const int *const lists[],
    const size_t lengths[],
    size_t list_count,
    long long *maximum_sum)
{
    long long maximum = 0;

    if (lists == NULL || lengths == NULL ||
        maximum_sum == NULL || list_count == 0) {
        return SUM_STATUS_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < list_count; ++i) {
        long long sum = 0;

        if (lengths[i] > 0 && lists[i] == NULL) {
            return SUM_STATUS_INVALID_ARGUMENT;
        }

        for (size_t j = 0; j < lengths[i]; ++j) {
            if (!checked_add(sum, lists[i][j], &sum)) {
                return SUM_STATUS_OVERFLOW;
            }
        }

        if (i == 0 || sum > maximum) {
            maximum = sum;
        }
    }

    *maximum_sum = maximum;
    return SUM_STATUS_OK;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {-5, 10, 8};
    const int third[] = {4, 4, 4, 4};
    const int *lists[] = {first, second, third};
    const size_t lengths[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0])
    };
    long long maximum_sum = 0;
    SumStatus status = find_max_list_sum(
        lists,
        lengths,
        sizeof(lists) / sizeof(lists[0]),
        &maximum_sum
    );

    if (status == SUM_STATUS_INVALID_ARGUMENT) {
        fputs("Invalid argument\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == SUM_STATUS_OVERFLOW) {
        fputs("Sum overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", maximum_sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}