#include <stdio.h>

void find_vertex(double a, double b, double c, double *x, double *y) {
    *x = -b / (2 * a);
    *y = c - (b * b) / (4 * a);
}

int main() {
    double a, b, c;
    double x, y;

    printf("Enter coefficients a, b and c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0) {
        printf("Coefficient 'a' must not be zero for a valid parabola.\n");
        return 1;
    }

    find_vertex(a, b, c, &x, &y);

    printf("Vertex of the parabola is at (x, y): (%.2f, %.2f)\n", x, y);

    return 0;
}