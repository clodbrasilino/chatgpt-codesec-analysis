#include <stdio.h>
#include <math.h>

int find_number_of_solutions(double a, double b, double c) {
    if (fabs(a) < 1e-12) {
        if (fabs(b) < 1e-12) {
            if (fabs(c) < 1e-12) {
                return -1;
            }
            return 0;
        }
        return 1;
    }

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant > 1e-12) {
        return 2;
    } else if (fabs(discriminant) <= 1e-12) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    double a = 1.0;
    double b = -3.0;
    double c = 2.0;

    int solutions = find_number_of_solutions(a, b, c);

    if (solutions == -1) {
        printf("Infinite solutions\n");
    } else {
        printf("Number of solutions: %d\n", solutions);
    }

    return 0;
}