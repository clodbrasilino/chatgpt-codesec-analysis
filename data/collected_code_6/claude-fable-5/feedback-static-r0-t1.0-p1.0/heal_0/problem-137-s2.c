#include <stdio.h>
#include <stddef.h>

double zero_ratio(const int *arr, size_t len)
{
    size_t count = 0;
    size_t i;

    if (arr == NULL || len == 0) {
        return 0.0;
    }

    for (i = 0; i < len; i++) {
        if (arr[i] == 0) {
            count++;
        }
    }

    return (double)count / (double)len;
}

int main(void)
{
    int data[] = {0, 5, 0, 3, 7, 0, 1, 0};
    size_t len = sizeof(data) / sizeof(data[0]);
    double ratio;

    ratio = zero_ratio(data, len);

    if (printf("Ratio of zeroes: %f\n", ratio) < 0) {
        return 1;
    }

    return 0;
}