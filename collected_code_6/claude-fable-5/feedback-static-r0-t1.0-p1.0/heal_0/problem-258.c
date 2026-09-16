#include <stdio.h>
#include <stdlib.h>

size_t count_odd_elements(const int *arr, size_t len)
{
    size_t count = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count;

    odd_count = count_odd_elements(numbers, len);

    if (printf("Number of odd elements: %zu\n", odd_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}