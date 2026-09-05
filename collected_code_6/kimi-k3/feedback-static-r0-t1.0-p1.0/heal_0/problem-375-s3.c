#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <limits.h>

int round_to_multiple(double number, double multiple, double *result) {
    if (result == NULL) {
        return -1;
    }
    if (multiple == 0.0) {
        return -1;
    }
    if (!isfinite(number) || !isfinite(multiple)) {
        return -1;
    }
    
    double quotient = number / multiple;
    double rounded_quotient = round(quotient);
    
    if (fabs(rounded_quotient) > (double)LLONG_MAX) {
        return -1;
    }
    
    *result = rounded_quotient * multiple;
    return 0;
}

int main(void) {
    double number, multiple, result;
    
    printf("Enter number: ");
    if (scanf("%lf", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter multiple: ");
    if (scanf("%lf", &multiple) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (round_to_multiple(number, multiple, &result) != 0) {
        fprintf(stderr, "Error: invalid parameters or overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %.2f\n", result);
    return EXIT_SUCCESS;
}