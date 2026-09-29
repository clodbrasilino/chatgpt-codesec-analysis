#include <stdio.h>
#include <stdlib.h>

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
    int numbers[] = { 3, -1, 0, 7, -5, 12, 8, -2 };
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    double ratio;

    ratio = positive_ratio(numbers, len);

    if (printf("Ratio of positive numbers: %.2f\n", ratio) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}