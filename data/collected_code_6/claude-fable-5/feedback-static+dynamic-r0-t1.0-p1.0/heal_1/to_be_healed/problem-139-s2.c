#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
 /* Possible weaknesses found:
  *  test case 1 failed: expected 31.415000000000003, got 31.415925979614258
  *  test case 0 failed: expected 62.830000000000005, got 62.831851959228516
  *  test case 2 failed: expected 25.132, got 25.132741928100586
  */

double circle_circumference(double radius)
{
    return 2.0 * M_PI * radius;
}

int main(void)
{
    double radius;
    double circumference;

    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(radius)) {
        fprintf(stderr, "Error: radius must be a finite number.\n");
        return EXIT_FAILURE;
    }

    circumference = circle_circumference(radius);

    if (!isfinite(circumference)) {
        fprintf(stderr, "Error: result overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Circumference: %f\n", circumference);

    return EXIT_SUCCESS;
}