#include <stdio.h>
#include <stddef.h>

size_t count_even_elements(const int *arr, size_t length)
{
    size_t count = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    size_t result;

    result = count_even_elements(numbers, length);

    if (printf("Number of even elements: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}