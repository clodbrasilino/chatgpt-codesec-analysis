#include <stddef.h>
#include <stdio.h>

static double negative_ratio(const int *array, size_t length)
{
    size_t negative_count = 0;

    if (array == NULL || length == 0) {
        return 0.0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] < 0) {
            ++negative_count;
        }
    }

    return (double)negative_count / (double)length;
}

int main(void)
{
    const int values[] = {-5, 3, -2, 0, 8, -1};
    const size_t length = sizeof(values) / sizeof(values[0]);
    const double ratio = negative_ratio(values, length);

    if (printf("%.6f\n", ratio) < 0) {
        return 1;
    }

    return 0;
}