#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_power(double base, double exponent) {
    return pow(base, exponent);
}

double *map_power(double base, const double *indices, size_t count, double (*func)(double, double)) {
    if (count == 0) {
        return NULL;
    }
    
    double *result = malloc(count * sizeof(double));
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < count; i++) {
        result[i] = func(base, indices[i]);
    }
    
    return result;
}

int main(void) {
    double base = 2.0;
    double indices[] = {0.0, 1.0, 2.0, 3.0, 4.0};
    size_t count = sizeof(indices) / sizeof(indices[0]);
    
    double *result = map_power(base, indices, count, calculate_power);
    
    if (result != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%.2f ", result[i]);
        }
        printf("\n");
        
        free(result);
        result = NULL;
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return 1;
    }
    
    return 0;
}