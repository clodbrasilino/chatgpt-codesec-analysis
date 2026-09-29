#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double largest_triangle_area(double semi_major, double semi_minor);
 /* Possible weaknesses found:
  *  test case 2 failed: expected 105.2220865598093, got 11.691343307495117
  *  test case 1 failed: expected 4.639421805988064, got 45.466335296630859
  */

double largest_triangle_area(double semi_major, double semi_minor)
{
    if (!isfinite(semi_major) || !isfinite(semi_minor))
    {
        return -1.0;
    }

    if (semi_major <= 0.0 || semi_minor <= 0.0)
    {
        return -1.0;
    }

    if (semi_minor > semi_major)
    {
        double tmp = semi_major;
        semi_major = semi_minor;
        semi_minor = tmp;
    }

    return (3.0 * sqrt(3.0) / 4.0) * semi_major * semi_minor;
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double area = 0.0;

    printf("Enter semi-major axis (a): ");
    if (scanf("%lf", &a) != 1)
    {
        fprintf(stderr, "Error: invalid input for semi-major axis.\n");
        return EXIT_FAILURE;
    }

    printf("Enter semi-minor axis (b): ");
    if (scanf("%lf", &b) != 1)
    {
        fprintf(stderr, "Error: invalid input for semi-minor axis.\n");
        return EXIT_FAILURE;
    }

    area = largest_triangle_area(a, b);

    if (area < 0.0)
    {
        fprintf(stderr, "Error: axes must be positive finite values.\n");
        return EXIT_FAILURE;
    }

    printf("Largest inscribed triangle area: %.15g\n", area);

    return EXIT_SUCCESS;
}