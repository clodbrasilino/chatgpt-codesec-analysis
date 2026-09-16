#include <stddef.h>
#include <stdio.h>

static size_t count_positive(const int *numbers, size_t length)
{
    size_t count = 0;

    if (numbers == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (numbers[i] > 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    const int numbers[] = {-4, 7, 0, 12, -3, 5};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    const size_t count = count_positive(numbers, length);

    if (printf("%zu\n", count) < 0) {
        return 1;
    }

    return 0;
}