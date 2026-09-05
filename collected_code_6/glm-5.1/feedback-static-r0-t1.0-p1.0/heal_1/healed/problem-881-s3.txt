#include <stdio.h>
#include <stdlib.h>

void find_sums(const int *list, size_t size, int *sum_even, int *sum_odd) {
    if (list == NULL || sum_even == NULL || sum_odd == NULL) {
        return;
    }

    *sum_even = 0;
    *sum_odd = 0;

    int found_even = 0;
    int found_odd = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            if (!found_even) {
                *sum_even = list[i];
                found_even = 1;
            }
        } else {
            if (!found_odd) {
                *sum_odd = list[i];
                found_odd = 1;
            }
        }
    }
}

int main(void) {
    int list[] = {1, 3, 5, 2, 4, 7, 6, 8, 9};
    size_t size = sizeof(list) / sizeof(list[0]);
    int sum_even = 0;
    int sum_odd = 0;

    find_sums(list, size, &sum_even, &sum_odd);

    printf("Sum of first even number: %d\n", sum_even);
    printf("Sum of first odd number: %d\n", sum_odd);

    return 0;
}