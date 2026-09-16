#include <stdio.h>
#include <stddef.h>

int find_division_even_odd(const int *arr, size_t size, double *result)
{
    size_t i;
    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;

    if (arr == NULL || result == NULL || size == 0U) {
        return -1;
    }

    for (i = 0U; i < size; i++) {
        if (!found_even && (arr[i] % 2 == 0)) {
            first_even = arr[i];
            found_even = 1;
        }
        if (!found_odd && (arr[i] % 2 != 0)) {
            first_odd = arr[i];
            found_odd = 1;
        }
        if (found_even && found_odd) {
            break;
        }
    }

    if (!found_even || !found_odd) {
        return -1;
    }

    if (first_odd == 0) {
        return -1;
    }

    *result = (double)first_even / (double)first_odd;
    return 0;
}

int main(void)
{
    int numbers[] = {10, 3, 8, 5, 7, 2};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    double result = 0.0;
    int status;

    status = find_division_even_odd(numbers, size, &result);
    if (status != 0) {
        if (fprintf(stderr, "Error: could not compute division\n") < 0) {
            return 1;
        }
        return 1;
    }

    if (printf("Division of first even by first odd: %f\n", result) < 0) {
        return 1;
    }

    return 0;
}