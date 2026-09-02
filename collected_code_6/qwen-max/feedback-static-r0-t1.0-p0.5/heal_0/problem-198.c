#include <stdio.h>
#include <math.h>

double ellipse_area(double a, double b) {
    return M_PI * a * b;
}

double triangle_area(double a, double b) {
    return 0.5 * a * b;
}

double inscribed_triangle_area(double a, double b) {
    double x = sqrt(3.0) / 2.0 * a;
    double y = b / 2.0;
    return 3.0 * triangle_area(x, y);
}

int main() {
    double a, b;
    printf("Enter the semi-major axis (a) and semi-minor axis (b) of the ellipse: ");
    if (scanf("%lf %lf", &a, &b) != 2) {
        return 1;
    }
    double area = inscribed_triangle_area(a, b);
    printf("The area of the largest inscribed triangle is: %.2f\n", area);
    return 0;
}