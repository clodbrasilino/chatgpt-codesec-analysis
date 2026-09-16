#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculate_directrix(double a, double b, double c, double *directrix) {
    if (directrix == NULL) {
        return;
    }
    
    if (fabs(a) < 1e-9) {
        return;
    }

    *directrix = c - ((b * b) + 1.0) / (4.0 * a);
}

int main(void) {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double directrix = 0.0;
    int result = 0;

    printf("Enter coefficients a, b, and c (for y = ax^2 + bx + c): ");
    result = scanf("%lf %lf %lf", &a, &b, &c);

    if (result != 3) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (fabs(a) < 1e-9) {
        printf("Coefficient 'a' cannot be zero for a parabola.\n");
        return EXIT_FAILURE;
    }

    calculate_directrix(a, b, c, &directrix);

    printf("The directrix of the parabola is y = %.4lf\n", directrix);

    return EXIT_SUCCESS;
}