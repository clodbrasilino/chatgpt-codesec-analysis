#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

double process_list(const double *numbers, size_t length)
{
    double sum = 0.0;
    size_t i;

    if (numbers == NULL || length == 0) {
        return 0.0;
    }

    for (i = 0; i < length; i++) {
        sum += round(numbers[i]);
    }

    return sum * (double)length;
}

int main(void)
{
    double numbers[] = {1.2, 2.7, 3.5, 4.4, 5.9};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    double result;

    result = process_list(numbers, length);

    if (printf("Result: %.2f\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}