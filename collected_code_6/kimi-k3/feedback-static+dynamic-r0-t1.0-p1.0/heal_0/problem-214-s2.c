#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>

double radians_to_degrees(double radians)
{
    if (!isfinite(radians))
    {
        errno = EDOM;
        return NAN;
    }
    return radians * (180.0 / M_PI);
}

int main(void)
{
    double radians = 0.0;
    double degrees = 0.0;
    int scan_result = 0;

    printf("Enter angle in radians: ");
    scan_result = scanf("%lf", &radians);
    
    if (scan_result != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    degrees = radians_to_degrees(radians);
    
    if (errno == EDOM)
    {
        fprintf(stderr, "Invalid input value\n");
        return EXIT_FAILURE;
    }

    printf("%.6f radians is %.6f degrees\n", radians, degrees);
    return EXIT_SUCCESS;
}