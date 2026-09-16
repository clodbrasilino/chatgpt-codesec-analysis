#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void power_of_elements(const double *input, double *output, size_t size, double n) {
    if (input == NULL || output == NULL) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        output[i] = pow(input[i], n);
    }
}

int main(void) {
    size_t size = 5;
    double n = 3.0;
    
    double *input = (double *)malloc(size * sizeof(double));
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    double *output = (double *)malloc(size * sizeof(double));
    if (output == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    input[0] = 1.0;
    input[1] = 2.0;
    input[2] = 3.0;
    input[3] = 4.0;
    input[4] = 5.0;

    power_of_elements(input, output, size, n);

    for (size_t i = 0; i < size; ++i) {
        printf("%f\n", output[i]);
    }

    free(input);
    free(output);

    return EXIT_SUCCESS;
}