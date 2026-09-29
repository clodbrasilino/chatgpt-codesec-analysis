#include <stdio.h>
#include <stddef.h>

size_t count_odd_elements(const int arr[], size_t size)
{
    size_t count = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count;

    odd_count = count_odd_elements(numbers, size);

    printf("Number of odd elements: %zu\n", odd_count);

    return 0;
}