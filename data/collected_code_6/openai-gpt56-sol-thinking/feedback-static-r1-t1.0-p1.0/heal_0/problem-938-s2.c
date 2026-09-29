#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool find_three_closest(const int first[], size_t first_length,
                        const int second[], size_t second_length,
                        const int third[], size_t third_length,
                        int *first_result,
                        int *second_result,
                        int *third_result)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    int64_t best_difference = INT64_MAX;

    if (first == NULL || second == NULL || third == NULL ||
        first_result == NULL || second_result == NULL || third_result == NULL ||
        first_length == 0 || second_length == 0 || third_length == 0) {
        return false;
    }

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

        int64_t difference = (int64_t)maximum - (int64_t)minimum;

        if (difference < best_difference) {
            best_difference = difference;
            *first_result = first[i];
            *second_result = second[j];
            *third_result = third[k];
        }

        if (best_difference == 0) {
            break;
        }

        if (first[i] == minimum) {
            ++i;
        } else if (second[j] == minimum) {
            ++j;
        } else {
            ++k;
        }
    }

    return true;
}

int main(void)
{
    const int first[] = {1, 4, 10};
    const int second[] = {2, 15, 20};
    const int third[] = {10, 12};
    int first_result;
    int second_result;
    int third_result;

    if (!find_three_closest(first, sizeof(first) / sizeof(first[0]),
                            second, sizeof(second) / sizeof(second[0]),
                            third, sizeof(third) / sizeof(third[0]),
                            &first_result, &second_result, &third_result)) {
        return EXIT_FAILURE;
    }

    if (printf("%d %d %d\n",
               first_result, second_result, third_result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}