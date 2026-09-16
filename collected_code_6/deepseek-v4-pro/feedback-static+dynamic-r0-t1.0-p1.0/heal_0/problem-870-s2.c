#include <stdio.h>
#include <stdlib.h>

double sum_positive_numbers(const double *numbers, size_t count, int *error_flag) {
    double sum = 0.0;
    size_t i;

    if (numbers == NULL && count > 0) {
        if (error_flag != NULL) {
            *error_flag = 1;
        }
        return 0.0;
    }

    if (error_flag != NULL) {
        *error_flag = 0;
    }

    for (i = 0; i < count; i++) {
        if (numbers[i] > 0.0) {
            sum += numbers[i];
        }
    }

    return sum;
}

int main(void) {
    double numbers[] = {-2.5, 3.0, 0.0, 4.5, -1.0, 2.0};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int error_flag = 0;
    double result;

    result = sum_positive_numbers(numbers, count, &error_flag);

    if (error_flag != 0) {
        fprintf(stderr, "Error: Invalid input to sum_positive_numbers\n");
        return EXIT_FAILURE;
    }

    printf("Sum of positive numbers: %.2f\n", result);

    return EXIT_SUCCESS;
}