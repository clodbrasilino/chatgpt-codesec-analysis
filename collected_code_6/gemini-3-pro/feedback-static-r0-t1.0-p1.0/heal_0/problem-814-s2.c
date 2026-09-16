#include <stdio.h>
#include <stdlib.h>

int calculate_rhombus_area(double diagonal1, double diagonal2, double *area) {
    if (diagonal1 <= 0.0 || diagonal2 <= 0.0 || area == NULL) {
        return -1;
    }
    *area = (diagonal1 * diagonal2) / 2.0;
    return 0;
}

int main(void) {
    double d1 = 0.0;
    double d2 = 0.0;
    double area = 0.0;

    if (scanf("%lf %lf", &d1, &d2) != 2) {
        return EXIT_FAILURE;
    }

    if (calculate_rhombus_area(d1, d2, &area) != 0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}