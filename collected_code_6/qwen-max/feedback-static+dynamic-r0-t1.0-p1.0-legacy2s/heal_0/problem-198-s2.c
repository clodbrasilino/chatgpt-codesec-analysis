#include <stdio.h>
#include <math.h>

double ellipse_area(double a, double b) {
    return M_PI * a * b;
}

void largest_triangle_in_ellipse(double a, double b, double *area, double *x1, double *y1, double *x2, double *y2, double *x3, double *y3) {
    if (a <= 0 || b <= 0) return;

    *area = 3.0 / 4.0 * sqrt(3) * a * b;
    *x1 = -a;
    *y1 = 0;
    *x2 = a / 2;
    *y2 = sqrt(3) * b / 2;
    *x3 = a / 2;
    *y3 = -sqrt(3) * b / 2;
}

int main() {
    double a = 5.0;
    double b = 3.0;
    double area, x1, y1, x2, y2, x3, y3;

    largest_triangle_in_ellipse(a, b, &area, &x1, &y1, &x2, &y2, &x3, &y3);

    printf("Area of the largest inscribed triangle: %f\n", area);
    printf("Vertices: (%f, %f), (%f, %f), (%f, %f)\n", x1, y1, x2, y2, x3, y3);

    return 0;
}