#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

double negative_ratio(const int *arr, size_t size, int *status)
{
    size_t i;
    size_t count = 0;

    if (arr == NULL || size == 0 || status == NULL) {
        if (status != NULL) {
            *status = -1;
        }
        return 0.0;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] < 0) {
            count++;
        }
    }

    *status = 0;
    return (double)count / (double)size;
}

int main(void)
{
    int numbers[] = { -3, 5, -7, 12, 0, -1, 8, -4 };
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int status = 0;
    double ratio;

    ratio = negative_ratio(numbers, size, &status);

    if (status != 0) {
        if (fprintf(stderr, "Error: invalid input to negative_ratio\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Ratio of negative numbers: %f\n", ratio) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}