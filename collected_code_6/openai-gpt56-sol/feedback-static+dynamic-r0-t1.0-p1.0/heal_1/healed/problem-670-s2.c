#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool has_decreasing_trend(const double *numbers, size_t count)
{
    if (numbers == NULL || count < 2U) {
        return false;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (numbers[i] < numbers[i - 1U]) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const double numbers[] = {10.0, 8.5, 7.0, 3.5, 1.0};
    const size_t count = sizeof numbers / sizeof numbers[0];

    if (has_decreasing_trend(numbers, count)) {
        if (puts("The sequence has a decreasing trend.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The sequence does not have a decreasing trend.") == EOF) {
            return 1;
        }
    }

    return 0;
}