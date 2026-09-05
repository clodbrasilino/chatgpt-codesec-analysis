#include <stdio.h>
#include <math.h>
#include <complex.h>

double complex_length(double complex z)
{
    return cabs(z);
}

int main(void)
{
    double complex z = 3.0 + 4.0 * I;
    double length = complex_length(z);
    if (printf("Length: %f\n", length) < 0)
    {
        return 1;
    }
    return 0;
}