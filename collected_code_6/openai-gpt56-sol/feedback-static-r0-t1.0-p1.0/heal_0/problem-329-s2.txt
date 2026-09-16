#include <stddef.h>
#include <stdio.h>

static size_t count_negative_numbers(const int *numbers, size_t length)
{
    size_t count = 0U;

    if (numbers == NULL && length != 0U) {
        return 0U;
    }

    for (size_t i = 0U; i < length; ++i) {
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