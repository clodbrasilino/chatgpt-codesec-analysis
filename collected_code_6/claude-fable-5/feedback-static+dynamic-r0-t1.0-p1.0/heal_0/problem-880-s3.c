#include <stdio.h>
#include <math.h>

#define EPSILON 1e-9

int count_solutions(double a, double b, double c)
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
    if (discriminant < -EPSILON) {
        return 0;
    }
    return 1;
}

int main(void)
{
    double a;
    double b;
    double c;
    int result;

    printf("Enter coefficient a: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for coefficient a\n");
        return 1;
    }

    printf("Enter coefficient b: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for coefficient b\n");
        return 1;
    }

    printf("Enter coefficient c: ");
    if (scanf("%lf", &c) != 1) {
        fprintf(stderr, "Invalid input for coefficient c\n");
        return 1;
    }

    result = count_solutions(a, b, c);

    if (result == -1) {
        printf("Infinite number of solutions\n");
    } else {
        printf("Number of solutions: %d\n", result);
    }

    return 0;
}