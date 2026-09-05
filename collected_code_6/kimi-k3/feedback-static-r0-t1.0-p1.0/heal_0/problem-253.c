#include <stdio.h>
#include <stdlib.h>

size_t count_integers(const int *list, size_t size)
{
    size_t count = 0;
    size_t i;

    if (list == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        count++;
    }

    return count;
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t result;

    result = count_integers(numbers, size);

    printf("Number of integers: %zu\n", result);

    return 0;
}