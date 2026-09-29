#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int are_parallel(double a1, double b1, double a2, double b2)
{
    double cross;

    cross = (a1 * b2) - (a2 * b1);

    if (fabs(cross) < EPSILON) {
        return 1;
    }

    return 0;
}

int is_valid_line(double a, double b)
{
    if ((fabs(a) < EPSILON) && (fabs(b) < EPSILON)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    double a1;
    double b1;
    double c1;
    double a2;
    double b2;
    double c2;
    int result;

    printf("Enter coefficients a1, b1, c1 for the first line (a1*x + b1*y + c1 = 0): ");
    result = scanf("%lf %lf %lf", &a1, &b1, &c1);
    if (result != 3) {
        fprintf(stderr, "Error: invalid input for the first line.\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficients a2, b2, c2 for the second line (a2*x + b2*y + c2 = 0): ");
    result = scanf("%lf %lf %lf", &a2, &b2, &c2);
    if (result != 3) {
        fprintf(stderr, "Error: invalid input for the second line.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_line(a1, b1)) {
        fprintf(stderr, "Error: the first line is degenerate (a1 and b1 are both zero).\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_line(a2, b2)) {
        fprintf(stderr, "Error: the second line is degenerate (a2 and b2 are both zero).\n");
        return EXIT_FAILURE;
    }

    if (are_parallel(a1, b1, a2, b2)) {
        printf("The lines are parallel.\n");
    } else {
        printf("The lines are not parallel.\n");
    }

    return EXIT_SUCCESS;
}