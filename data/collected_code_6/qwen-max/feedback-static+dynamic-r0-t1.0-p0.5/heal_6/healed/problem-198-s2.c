#include <stdio.h>
#include <math.h>

double ellipse_area(double a, double b) {
    return M_PI * a * b;
}

double triangle_area(double a, double h) {
    return 0.5 * a * h;
}

double find_largest_triangle(double a, double b) {
    double max_area = 0.0;
    for (double theta = 0; theta <= 2 * M_PI; theta += 0.01) {
        double x1 = a * cos(theta);
        double y1 = b * sin(theta);
        double x2 = a * cos(theta + 2 * M_PI / 3);
        double y2 = b * sin(theta + 2 * M_PI / 3);
        double x3 = a * cos(theta + 4 * M_PI / 3);
        double y3 = b * sin(theta + 4 * M_PI / 3);

        double area = 0.5 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
        if (fabs(area) > max_area) {
            max_area = fabs(area);
        }
    }
    return max_area;
}

int main() {
    double a = 5.0;
    double b = 3.0;
    double largest_triangle_area = find_largest_triangle(a, b);
    printf("Largest inscribed triangle area: %f\n", largest_triangle_area);
    return 0;
}