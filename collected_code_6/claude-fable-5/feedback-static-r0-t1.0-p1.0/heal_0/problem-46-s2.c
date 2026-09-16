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

    if (count < 2U) {
        return true;
    }

    for (i = 0U; i < count - 1U; i++) {
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
    int set_a[] = { 1, 5, 7, 9, 12 };
    int set_b[] = { 3, 8, 3, 10 };
    size_t len_a = sizeof(set_a) / sizeof(set_a[0]);
    size_t len_b = sizeof(set_b) / sizeof(set_b[0]);

    if (all_numbers_different(set_a, len_a)) {
        if (printf("Set A: all numbers are different\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Set A: numbers are not all different\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (all_numbers_different(set_b, len_b)) {
        if (printf("Set B: all numbers are different\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Set B: numbers are not all different\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}