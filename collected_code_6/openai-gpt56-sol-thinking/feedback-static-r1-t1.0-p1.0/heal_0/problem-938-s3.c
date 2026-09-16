#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    int third;
} ClosestTriple;

typedef enum {
    CLOSEST_SUCCESS,
    CLOSEST_INVALID_ARGUMENT,
    CLOSEST_UNSORTED_ARRAY
} ClosestStatus;

static bool is_sorted(const int *array, size_t length)
{
    for (size_t i = 1; i < length; ++i) {
        if (array[i] < array[i - 1]) {
            return false;
        }
    }

    return true;
}

ClosestStatus find_three_closest(
    const int *first,
    size_t first_length,
    const int *second,
    size_t second_length,
    const int *third,
    size_t third_length,
    ClosestTriple *result)
{
    if (first == NULL || second == NULL || third == NULL || result == NULL ||
        first_length == 0 || second_length == 0 || third_length == 0) {
        return CLOSEST_INVALID_ARGUMENT;
    }

    if (!is_sorted(first, first_length) ||
        !is_sorted(second, second_length) ||
        !is_sorted(third, third_length)) {
        return CLOSEST_UNSORTED_ARRAY;
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    int64_t best_range = INT64_MAX;
    ClosestTriple best = {0, 0, 0};

    while (i < first_length && j < second_length && k < third_length) {
        int minimum = first[i];
        int maximum = first[i];

        if (second[j] < minimum) {
            minimum = second[j];
        }
        if (third[k] < minimum) {
            minimum = third[k];
        }
        if (second[j] > maximum) {
            maximum = second[j];
        }
        if (third[k] > maximum) {
            maximum = third[k];
        }

        int64_t current_range = (int64_t)maximum - (int64_t)minimum;

        if (current_range < best_range) {
            best_range = current_range;
            best.first = first[i];
            best.second = second[j];
            best.third = third[k];

            if (best_range == 0) {
                break;
            }
        }

        if (first[i] == minimum) {
            ++i;
        } else if (second[j] == minimum) {
            ++j;
        } else {
            ++k;
        }
    }

    *result = best;
    return CLOSEST_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 4, 10};
    const int second[] = {2, 15, 20};
    const int third[] = {10, 12};
    ClosestTriple result;

    ClosestStatus status = find_three_closest(
        first,
        sizeof(first) / sizeof(first[0]),
        second,
        sizeof(second) / sizeof(second[0]),
        third,
        sizeof(third) / sizeof(third[0]),
        &result);

    if (status != CLOSEST_SUCCESS) {
        fprintf(stderr, "Unable to find the closest elements.\n");
        return EXIT_FAILURE;
    }

    printf("%d %d %d\n", result.first, result.second, result.third);
    return EXIT_SUCCESS;
}