#include <stdio.h>
#include <stdlib.h>

int find_product(int *list, size_t size, int *product) {
    if (list == NULL || product == NULL || size == 0) {
        return -1;
    }

    int first_even = 0;
    int first_odd = 0;
    int has_even = 0;
    int has_odd = 0;

    for (size_t i = 0; i < size; i++) {
        if (!has_even && list[i] % 2 == 0) {
            first_even = list[i];
            has_even = 1;
        } else if (!has_odd && list[i] % 2 != 0) {
            first_odd = list[i];
            has_odd = 1;
        }

        if (has_even && has_odd) {
            break;
        }
    }

    if (!has_even || !has_odd) {
        return -1;
    }

    *product = first_even * first_odd;
    return 0;
}

int main(void) {
    int list[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    int product = 0;

    if (find_product(list, size, &product) == 0) {
        printf("%d\n", product);
    } else {
        printf("Invalid input or missing even/odd numbers\n");
    }

    return 0;
}