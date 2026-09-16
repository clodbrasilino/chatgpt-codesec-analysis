#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_numbers_different(const int *numbers, size_t count)
{
    size_t i;
    size_t j;

    if (numbers == NULL) {
        return false;
    }

    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (numbers[i] == numbers[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    int set1[] = {1, 2, 3, 4, 5};
    int set2[] = {1, 2, 3, 2, 5};
    size_t len1 = sizeof(set1) / sizeof(set1[0]);
    size_t len2 = sizeof(set2) / sizeof(set2[0]);

    if (all_numbers_different(set1, len1)) {
        if (printf("Set 1: all numbers are different\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Set 1: numbers are not all different\n") < 0) {
            return 1;
        }
    }

    if (all_numbers_different(set2, len2)) {
        if (printf("Set 2: all numbers are different\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Set 2: numbers are not all different\n") < 0) {
            return 1;
        }
    }

    return 0;
}