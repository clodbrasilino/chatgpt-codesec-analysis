#include <stdio.h>
#include <stdlib.h>

static int positive_ratio(const int *array, size_t length, double *ratio)
{
    size_t positive_count = 0;

    if (array == NULL || ratio == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] > 0) {
            ++positive_count;
        }
    }

    *ratio = (double)positive_count / (double)length;
    return 0;
}

int main(void)
{
    int numbers[] = {-4, 7, 0, 3, -2, 9};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    double ratio = 0.0;

    if (positive_ratio(numbers, length, &ratio) != 0) {
        fputs("Failed to calculate the ratio.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.6f\n", ratio) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}