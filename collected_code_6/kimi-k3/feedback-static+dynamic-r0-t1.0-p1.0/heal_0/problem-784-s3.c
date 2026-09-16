#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int product_first_even_odd(const int *arr, size_t size, int *result)
{
    bool found_even = false;
    bool found_odd = false;
    int first_even = 0;
    int first_odd = 0;

    if (arr == NULL || result == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (!found_even && arr[i] % 2 == 0) {
            first_even = arr[i];
            found_even = true;
        } else if (!found_odd && arr[i] % 2 != 0) {
            first_odd = arr[i];
            found_odd = true;
        }

        if (found_even && found_odd) {
            *result = first_even * first_odd;
            return 0;
        }
    }

    return -1;
}

int main(void)
{
    int numbers[] = {3, 7, 8, 5, 4, 2};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int result = 0;

    if (product_first_even_odd(numbers, size, &result) == 0) {
        printf("Product: %d\n", result);
    } else {
        printf("Could not find both even and odd numbers.\n");
    }

    return 0;
}