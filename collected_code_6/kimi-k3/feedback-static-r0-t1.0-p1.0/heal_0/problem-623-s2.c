#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

int power_elements(const double *input, size_t count, double exponent, double *output)
{
    size_t i;
    
    if (input == NULL || output == NULL || count == 0) {
        return -1;
    }
    
    errno = 0;
    
    for (i = 0; i < count; i++) {
        output[i] = pow(input[i], exponent);
        if (errno == EDOM || errno == ERANGE) {
            return -2;
        }
    }
    
    return 0;
}

int main(void)
{
    double numbers[] = {1.5, 2.0, 3.5, 4.0, 5.25};
    double results[5];
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    double exponent = 2.0;
    size_t i;
    int status;
    
    status = power_elements(numbers, count, exponent, results);
    
    if (status != 0) {
        fprintf(stderr, "Error: Operation failed with status %d\n", status);
        return EXIT_FAILURE;
    }
    
    printf("Original elements: ");
    for (i = 0; i < count; i++) {
        printf("%.2f ", numbers[i]);
    }
    printf("\n");
    
    printf("Elements raised to power %.2f: ", exponent);
    for (i = 0; i < count; i++) {
        printf("%.2f ", results[i]);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}