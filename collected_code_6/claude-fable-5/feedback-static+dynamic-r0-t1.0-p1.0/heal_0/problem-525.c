#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int areLinesParallel(double a1, double b1, double a2, double b2)
{
    double determinant = (a1 * b2) - (a2 * b1);
    if (fabs(determinant) < EPSILON) {
        return 1;
    }
    return 0;
}

int main(void)
{
    double a1;
    double b1;
    double c1;
    double a2;
    double b2;
    double c2;

    printf("Enter coefficients a1, b1, c1 for line 1 (a1*x + b1*y + c1 = 0): ");
    if (scanf("%lf %lf %lf", &a1, &b1, &c1) != 3) {
        fprintf(stderr, "Invalid input for line 1\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficients a2, b2, c2 for line 2 (a2*x + b2*y + c2 = 0): ");
    if (scanf("%lf %lf %lf", &a2, &b2, &c2) != 3) {
        fprintf(stderr, "Invalid input for line 2\n");
        return EXIT_FAILURE;
    }

    if ((fabs(a1) < EPSILON && fabs(b1) < EPSILON) ||
        (fabs(a2) < EPSILON && fabs(b2) < EPSILON)) {
        fprintf(stderr, "Invalid line: a and b cannot both be zero\n");
        return EXIT_FAILURE;
    }

    if (areLinesParallel(a1, b1, a2, b2) == 1) {
        printf("The lines are parallel.\n");
    } else {
        printf("The lines are not parallel.\n");
    }

    return EXIT_SUCCESS;
}