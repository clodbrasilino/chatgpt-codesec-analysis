#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <fenv.h>

double degrees_to_radians(double degrees)
{
    return degrees * (M_PI / 180.0);
}

int main(void)
{
    double degrees;
    double radians;
    int scan_result;

    printf("Enter angle in degrees: ");
    scan_result = scanf("%lf", &degrees);

    if (scan_result != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }

    if (!isfinite(degrees))
    {
        fprintf(stderr, "Error: Input must be a finite number\n");
        return 1;
    }

    errno = 0;
    feclearexcept(FE_ALL_EXCEPT);

    radians = degrees_to_radians(degrees);

    if (errno != 0 || fetestexcept(FE_OVERFLOW | FE_UNDERFLOW) != 0)
    {
        fprintf(stderr, "Error: Numerical computation error\n");
        return 1;
    }

    printf("%.10f degrees = %.10f radians\n", degrees, radians);

    return 0;
}