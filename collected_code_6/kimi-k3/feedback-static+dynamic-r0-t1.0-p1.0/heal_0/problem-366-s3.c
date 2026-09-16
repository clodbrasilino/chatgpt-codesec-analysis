#include <stdio.h>
#include <limits.h>

int largest_adjacent_product(const int arr[], size_t size, int *result)
{
    size_t i;
    int max_product;

    if (arr == NULL || result == NULL || size < 2) {
        return -1;
    }

    max_product = arr[0] * arr[1];
    for (i = 1; i < size - 1; i++) {
        int product = arr[i] * arr[i + 1];
        if (product > max_product) {
            max_product = product;
        }
    }

    *result = max_product;
    return 0;
}

int main(void)
{
    int numbers[] = {3, 6, -2, -5, 7, 3};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int result;

    if (largest_adjacent_product(numbers, size, &result) == 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    return 0;
}