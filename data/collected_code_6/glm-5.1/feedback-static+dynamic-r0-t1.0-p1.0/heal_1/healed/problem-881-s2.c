#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int sum_first_even;
    int sum_first_odd;
} SumResult;

SumResult find_sums(const int *list, size_t size) {
    SumResult result = {0, 0};
    int found_even = 0;
    int found_odd = 0;

    if (list == NULL) {
        return result;
    }

    for (size_t i = 0; i < size; i++) {
        if (!found_even && list[i] % 2 == 0) {
            result.sum_first_even += list[i];
            found_even = 1;
        } else if (!found_odd && list[i] % 2 != 0) {
            result.sum_first_odd += list[i];
            found_odd = 1;
        }

        if (found_even && found_odd) {
            break;
        }
    }

    return result;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    size_t size = sizeof(list) / sizeof(list[0]);

    SumResult result = find_sums(list, size);

    printf("Sum of first even: %d\n", result.sum_first_even);
    printf("Sum of first odd: %d\n", result.sum_first_odd);

    return 0;
}