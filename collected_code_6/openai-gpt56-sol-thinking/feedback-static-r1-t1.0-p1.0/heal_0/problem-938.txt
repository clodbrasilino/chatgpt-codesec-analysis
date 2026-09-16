#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sorted(const int array[], size_t length)
{
    if (array == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] < array[i - 1U]) {
            return false;
        }
    }

    return true;
}

bool find_three_closest(
    const int first[],
    size_t first_length,
    const int second[],
    size_t second_length,
    const int third[],
    size_t third_length,
    int *first_result,
    int *second_result,
    int *third_result)
{
    if (first_result == NULL || second_result == NULL || third_result == NULL ||
        !is_sorted(first, first_length) ||
        !is_sorted(second, second_length) ||
        !is_sorted(third, third_length)) {
        return false;
    }

    size_t i = 0U;
    size_t j = 0U;
    size_t k = 0U;
    int64_t smallest_range = INT64_MAX;

    while (i < first_length && j < second_length && k < third_length) {
        const int a = first[i];
        const int b = second[j];
        const int c = third[k];

        int minimum = a;
        int maximum = a;

        if (b < minimum) {
            minimum = b;
        }
        if (c < minimum) {
            minimum = c;
        }
        if (b > maximum) {
            maximum = b;
        }
        if (c > maximum) {
            maximum = c;
        }

        const int64_t range = (int64_t)maximum - (int64_t)minimum;

        if (range < smallest_range) {
            smallest_range = range;
            *first_result = a;
            *second_result = b;
            *third_result = c;

            if (range == 0) {
                return true;
            }
        }

        if (a <= b && a <= c) {
            ++i;
        } else if (b <= a && b <= c) {
            ++j;
        } else {
            ++k;
        }
    }

    return smallest_range != INT64_MAX;
}

int main(void)
{
    const int first[] = {1, 4, 10};
    const int second[] = {2, 15, 20};
    const int third[] = {10, 12};

    int first_result;
    int second_result;
    int third_result;

    const bool found = find_three_closest(
        first,
        sizeof(first) / sizeof(first[0]),
        second,
        sizeof(second) / sizeof(second[0]),
        third,
        sizeof(third) / sizeof(third[0]),
        &first_result,
        &second_result,
        &third_result);

    if (!found) {
        fputs("Unable to find three closest elements.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d %d %d\n", first_result, second_result, third_result);
    return EXIT_SUCCESS;
}