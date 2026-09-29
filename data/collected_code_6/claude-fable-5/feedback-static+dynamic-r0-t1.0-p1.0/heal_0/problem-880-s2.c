#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int number_of_solutions(double a, double b, double c)
{
    double discriminant;

    if (fabs(a) < EPSILON) {
        if (fabs(b) < EPSILON) {
            if (fabs(c) < EPSILON) {
                return -1;
            }
            return 0;
        }
        return 1;
    }

    discriminant = (b * b) - (4.0 * a * c);

    if (discriminant > EPSILON) {
        return 2;
    }
    if (fabs(discriminant) <= EPSILON) {
        return 1;
    }
    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    int result;

    printf("Enter coefficients a, b, c: ");

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = number_of_solutions(a, b, c);

    if (result == -1) {
        printf("The equation has infinitely many solutions.\n");
    } else {
        printf("The equation has %d solution(s).\n", result);
    }

    return EXIT_SUCCESS;
}