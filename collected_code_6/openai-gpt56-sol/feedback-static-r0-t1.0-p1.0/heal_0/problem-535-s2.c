#include <stdio.h>
#include <math.h>

static double cylinder_surface_area(double radius)
{
    return M_PI * radius * radius;
}

int main(void)
{
    double radius;

    if (printf("Enter the cylinder radius: ") < 0) {
        return 1;
    }

    if (fflush(stdout) == EOF) {
        return 1;
    }

    if (scanf("%lf", &radius) != 1 || !isfinite(radius) || radius < 0.0) {
        fputs("Invalid radius.\n", stderr);
        return 1;
    }

    const double area = cylinder_surface_area(radius);

    if (!isfinite(area)) {
        fputs("Area is outside the representable range.\n", stderr);
        return 1;
    }

    if (printf("Top or bottom surface area: %.6f\n", area) < 0) {
        return 1;
    }

    return 0;
}