#include <stdio.h>
#include <stddef.h>

double positive_ratio(const int *arr, size_t len)
{
    size_t i;
    size_t count = 0;

    if (arr == NULL || len == 0) {
        return 0.0;
    }

    for (i = 0; i < len; i++) {
        if (arr[i] > 0) {
            count++;
        }
    }

    return (double)count / (double)len;
}

int main(void)
{
    int numbers[] = { 3, -1, 7, 0, -5, 9, 2, -8 };
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    double ratio;

    ratio = positive_ratio(numbers, len);

    if (printf("Ratio of positive numbers: %.4f\n", ratio) < 0) {
        return 1;
    }

    return 0;
}