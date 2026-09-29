#include <stdio.h>
#include <stddef.h>

static double negative_ratio(const int values[], size_t count)
{
    size_t negative_count = 0U;

    if (values == NULL || count == 0U) {
        return 0.0;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] < 0) {
            ++negative_count;
        }
    }

    return (double)negative_count / (double)count;
}

int main(void)
{
    const int values[] = {-5, 3, -2, 0, 8, -1};
    const size_t count = sizeof(values) / sizeof(values[0]);

    if (printf("%.6f\n", negative_ratio(values, count)) < 0) {
        return 1;
    }

    return 0;
}