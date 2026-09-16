#include <stddef.h>
#include <stdio.h>

static size_t count_negative_numbers(const int *numbers, size_t length)
{
    size_t count = 0;

    if (numbers == NULL && length != 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (numbers[i] < 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    const int numbers[] = {4, -2, 0, -7, 9, -1};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    const size_t negative_count = count_negative_numbers(numbers, length);

    if (printf("%zu\n", negative_count) < 0) {
        return 1;
    }

    return 0;
}