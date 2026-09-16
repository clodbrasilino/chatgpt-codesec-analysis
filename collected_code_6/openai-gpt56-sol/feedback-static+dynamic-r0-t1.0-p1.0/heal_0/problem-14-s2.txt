#include <errno.h>
#include <math.h>
#include <stdio.h>

static int triangular_prism_volume(double base, double height, double length, double *volume)
{
    if (volume == NULL || !isfinite(base) || !isfinite(height) ||
        !isfinite(length) || base < 0.0 || height < 0.0 || length < 0.0) {
        return 0;
    }

    *volume = 0.5 * base * height * length;
    return isfinite(*volume);
}

int main(void)
{
    double base;
    double height;
    double length;
    double volume;

    errno = 0;
    if (scanf("%lf %lf %lf", &base, &height, &length) != 3 || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!triangular_prism_volume(base, height, length, &volume)) {
        fputs("Unable to calculate volume\n", stderr);
        return 1;
    }

    if (printf("%.6f\n", volume) < 0) {
        return 1;
    }

    return 0;
}