#include <stdio.h>
#include <stdlib.h>

double negative_ratio(const int *arr, size_t size)
{
    size_t i;
    size_t count = 0;

    if (arr == NULL || size == 0) {
        return 0.0;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] < 0) {
            count++;
        }
    }

    return (double)count / (double)size;
}

int main(void)
{
    int numbers[] = { -3, 5, -7, 12, 0, -1, 8, -9 };
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    double ratio;

    ratio = negative_ratio(numbers, size);

    if (printf("Ratio of negative numbers: %f\n", ratio) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}