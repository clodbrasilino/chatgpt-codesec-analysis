#include <stdio.h>
#include <stddef.h>

size_t count_positive(const int *numbers, size_t length)
{
    size_t count = 0;
    size_t i;

    if (numbers == NULL) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (numbers[i] > 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = { -5, 3, 0, 12, -7, 8, 1, -2 };
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    size_t result;

    result = count_positive(numbers, length);

    if (printf("Positive count: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}