#include <stddef.h>
#include <stdio.h>

static double negative_ratio(const int values[], size_t count)
{
    size_t negative_count = 0;

    if (values == NULL || count == 0) {
        return 0.0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (values[i] < 0) {
            ++negative_count;
        }
    }

    return (double)negative_count / (double)count;
}

int main(void)
{
    const int values[] = {-4, 7, -2, 0, 9, -1};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const double ratio = negative_ratio(values, count);

    if (printf("%.6f\n", ratio) < 0) {
        return 1;
    }

    return 0;
}