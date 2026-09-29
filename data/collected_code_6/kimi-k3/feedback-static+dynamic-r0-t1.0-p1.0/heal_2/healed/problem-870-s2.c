#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

double sum_positive(const double *numbers, size_t count)
{
    double sum = 0.0;
    size_t i;

    if (numbers == NULL) {
        return 0.0;
    }

    for (i = 0; i < count; i++) {
        if (numbers[i] > 0.0) {
            sum += numbers[i];
        }
    }

    return sum;
}

int main(int argc, const char *argv[])
{
    double *numbers;
    size_t count = 0;
    double result;

    if (argc > 1) {
        count = (size_t)(argc - 1);
        numbers = (double *)malloc(count * sizeof(double));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        for (size_t i = 0; i < count; i++) {
            numbers[i] = atof(argv[i + 1]);
        }
    } else {
        static double default_numbers[] = {1.5, -2.0, 3.2, -4.8, 5.0};
        count = sizeof(default_numbers) / sizeof(default_numbers[0]);
        numbers = (double *)malloc(count * sizeof(double));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        memcpy(numbers, default_numbers, count * sizeof(double));
    }

    result = sum_positive(numbers, count);

    printf("%.2f\n", result);

    free(numbers);

    return 0;
}