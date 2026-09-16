#include <stdio.h>
#include <math.h>

double ellipse_area(double a, double b) {
    return M_PI * a * b;
}

double max_triangle_area_ellipse(double a, double b) {
    double area = (3 * sqrt(3) / 4) * (a * b);
    return area;
}

int main() {
    double a, b;
    scanf("%lf %lf", &a, &b);
    double max_triangle_area = max_triangle_area_ellipse(a, b);
    printf("%.6f\n", max_triangle_area);
    return 0;
}