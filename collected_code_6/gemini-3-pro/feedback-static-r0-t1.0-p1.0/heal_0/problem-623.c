#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* calculate_powers(const double* elements, size_t count, double power) {
    if (elements == NULL || count == 0) {
        return NULL;
    }

    double* results = (double*)malloc(count * sizeof(double));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        results[i] = pow(elements[i], power);
    }

    return results;
}

int main(void) {
    double list[] = {2.0, 3.0, 4.5, 5.0};
    size_t count = sizeof(list) / sizeof(list[0]);
    double power = 3.0;

    double* powered_list = calculate_powers(list, count, power);

    if (powered_list != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%f ^ %f = %f\n", list[i], power, powered_list[i]);
        }
        free(powered_list);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}