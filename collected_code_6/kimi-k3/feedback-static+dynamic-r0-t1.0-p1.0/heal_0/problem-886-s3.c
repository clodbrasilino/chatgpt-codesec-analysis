#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

double calculate_average(const double *list, size_t length, int *error_flag)
{
    if (error_flag == NULL) {
        return NAN;
    }
    
    *error_flag = 0;
    
    if (list == NULL || length == 0) {
        *error_flag = EINVAL;
        return NAN;
    }
    
    double sum = 0.0;
    for (size_t i = 0; i < length; i++) {
        if (isnan(list[i]) || isinf(list[i])) {
            *error_flag = EDOM;
            return NAN;
        }
        
        if (fabs(list[i]) > DBL_MAX - sum) {
            *error_flag = ERANGE;
            return NAN;
        }
        
        sum += list[i];
    }
    
    return sum / (double)length;
}

int main(void)
{
    double numbers[] = {10.5, 20.3, 30.7, 40.2, 50.9};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int error_flag = 0;
    
    double average = calculate_average(numbers, length, &error_flag);
    
    if (error_flag != 0) {
        fprintf(stderr, "Error calculating average: %d\n", error_flag);
        return EXIT_FAILURE;
    }
    
    if (isnan(average)) {
        fprintf(stderr, "Invalid result\n");
        return EXIT_FAILURE;
    }
    
    printf("Average: %.2f\n", average);
    
    return EXIT_SUCCESS;
}