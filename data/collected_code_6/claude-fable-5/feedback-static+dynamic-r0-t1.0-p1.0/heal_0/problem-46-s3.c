#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool all_numbers_different(const int *numbers, size_t count)
{
    size_t i;
    size_t j;

    if (numbers == NULL) {
        return false;
    }

    for (i = 0U; i < count; i++) {
        for (j = i + 1U; j < count; j++) {
            if (numbers[i] == numbers[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    int values1[] = { 1, 2, 3, 4, 5 };
    int values2[] = { 1, 2, 3, 2, 5 };
    size_t count1 = sizeof(values1) / sizeof(values1[0]);
    size_t count2 = sizeof(values2) / sizeof(values2[0]);

    if (all_numbers_different(values1, count1)) {
        if (printf("Set 1: all numbers are different\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Set 1: numbers are not all different\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (all_numbers_different(values2, count2)) {
        if (printf("Set 2: all numbers are different\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Set 2: numbers are not all different\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}