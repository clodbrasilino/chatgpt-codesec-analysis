#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846
 /* Possible weaknesses found:
  *  test case 1 failed: expected 31.415000000000003, got 31.415925979614258
  *  test case 0 failed: expected 62.830000000000005, got 62.831851959228516
  *  test case 2 failed: expected 25.132, got 25.132741928100586
  */

double circle_circumference(double radius)
{
    return 2.0 * PI * radius;
}

int main(void)
{
    double radius;
    int result;

    printf("Enter the radius of the circle: ");
    result = scanf("%lf", &radius);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Circumference: %.6f\n", circle_circumference(radius));

    return EXIT_SUCCESS;
}