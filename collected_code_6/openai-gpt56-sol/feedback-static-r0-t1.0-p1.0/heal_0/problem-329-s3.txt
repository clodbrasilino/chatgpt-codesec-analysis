#include <stddef.h>
#include <stdio.h>

static size_t count_negative_numbers(const int values[], size_t length)
{
    size_t count = 0;

    if (values == NULL && length != 0U) {
        return 0U;
    }

    for (size_t i = 0; i < length; ++i) {
        if (values[i] < 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    const int values[] = {4, -2, 0, -7, 9, -1};
    const size_t length = sizeof values / sizeof values[0];
    const size_t negative_count = count_negative_numbers(values, length);

    if (printf("%zu\n", negative_count) < 0) {
        return 1;
    }

    return 0;
}