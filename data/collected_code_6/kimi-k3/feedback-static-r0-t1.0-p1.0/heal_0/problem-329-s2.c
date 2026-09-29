#include <stdio.h>
#include <stddef.h>

size_t count_negative_numbers(const int *list, size_t length)
{
    size_t count = 0;
    size_t i;

    if (list == NULL) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (list[i] < 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = {4, -3, 7, -1, 0, -9, 12};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    size_t negative_count;

    negative_count = count_negative_numbers(numbers, length);

    printf("Number of negative numbers: %zu\n", negative_count);

    return 0;
}