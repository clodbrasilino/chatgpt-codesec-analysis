#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

double calculate_stddev(const double *data, size_t size) {
    if (data == NULL || size == 0) {
        errno = EINVAL;
        return NAN;
    }
    
    double sum = 0.0;
    for (size_t i = 0; i < size; i++) {
        sum += data[i];
    }
    double mean = sum / size;
    
    double sum_sq_diff = 0.0;
    for (size_t i = 0; i < size; i++) {
        double diff = data[i] - mean;
        sum_sq_diff += diff * diff;
    }
    
    return sqrt(sum_sq_diff / size);
}

int main(void) {
    size_t n = 0;
    
    if (printf("Enter number of elements: ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%zu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n == 0) {
        fprintf(stderr, "Array size must be greater than 0\n");
        return EXIT_FAILURE;
    }
    
    double *arr = malloc(n * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    if (printf("Enter %zu elements: ", n) < 0) {
        free(arr);
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        if (scanf("%lf", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    errno = 0;
    double stddev = calculate_stddev(arr, n);
    
    if (errno != 0) {
        fprintf(stderr, "Calculation error\n");
        free(arr);
        return EXIT_FAILURE;
    }
    
    if (printf("Standard deviation: %.6f\n", stddev) < 0) {
        free(arr);
        return EXIT_FAILURE;
    }
    
    free(arr);
    return EXIT_SUCCESS;
}