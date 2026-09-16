#include <stdio.h>
#include <stdlib.h>

int find_sum_first_even_odd(const int *list, int size, int *sum_even, int *sum_odd) {
    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;
    int i;

    for (i = 0; i < size; i++) {
        if (list[i] % 2 == 0 && !found_even) {
            first_even = list[i];
            found_even = 1;
        } else if (list[i] % 2 != 0 && !found_odd) {
            first_odd = list[i];
            found_odd = 1;
        }
        if (found_even && found_odd) {
            break;
        }
    }

    if (!found_even || !found_odd) {
        return -1;
    }

    *sum_even = first_even;
    *sum_odd = first_odd;
    return 0;
}

int main(void) {
    int list[] = {3, 2, 5, 7, 10, 12};
    int size = sizeof(list) / sizeof(list[0]);
    int sum_even, sum_odd;
    int result;

    result = find_sum_first_even_odd(list, size, &sum_even, &sum_odd);

    if (result == 0) {
        printf("First even: %d\n", sum_even);
        printf("First odd: %d\n", sum_odd);
        printf("Sum: %d\n", sum_even + sum_odd);
    } else {
        printf("List does not contain both even and odd numbers.\n");
    }

    return 0;
}