#include <stdio.h>
#include <stddef.h>

size_t find_frequency(const int *arr, size_t size, int target)
{
    size_t count = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] == target) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = {4, 7, 2, 4, 9, 4, 1, 7, 4};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int target = 4;
    size_t frequency;

    frequency = find_frequency(numbers, size, target);

    if (printf("The number %d appears %zu time(s) in the array.\n", target, frequency) < 0) {
        return 1;
    }

    return 0;
}