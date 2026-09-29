#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculate_rounded_sum(const double *numbers, size_t length) {
    if (numbers == NULL || length == 0) {
        printf("Result: 0\n");
        return;
    }

    double sum = 0.0;

    for (size_t i = 0; i < length; i++) {
        sum += round(numbers[i]);
    }

    double result = sum * (double)length;
    printf("Result: %.0f\n", result);
}

int main(void) {
    double numbers[] = {1.2, 2.5, 3.8, 4.1, 5.9};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);

    calculate_rounded_sum(numbers, length);

    return EXIT_SUCCESS;
}