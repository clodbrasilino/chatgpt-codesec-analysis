#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_product_even(const int *numbers, size_t count)
{
    size_t i;

    if (numbers == NULL || count == 0U) {
        return false;
    }

    for (i = 0U; i < count; i++) {
        if ((numbers[i] % 2) == 0) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    int values_even[] = {3, 5, 7, 4};
    int values_odd[] = {3, 5, 7, 9};
    size_t count_even = sizeof(values_even) / sizeof(values_even[0]);
    size_t count_odd = sizeof(values_odd) / sizeof(values_odd[0]);

    if (is_product_even(values_even, count_even)) {
        if (printf("Product of first set is even\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Product of first set is odd\n") < 0) {
            return 1;
        }
    }

    if (is_product_even(values_odd, count_odd)) {
        if (printf("Product of second set is even\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Product of second set is odd\n") < 0) {
            return 1;
        }
    }

    return 0;
}