#include <stdio.h>
#include <math.h>

double ellipse_area(double a, double b) {
    return M_PI * a * b;
}

double triangle_area(double s1, double s2, double s3) {
    double s = (s1 + s2 + s3) / 2.0;
    return sqrt(s * (s - s1) * (s - s2) * (s - s3));
}

void find_largest_triangle(double a, double b, double *max_area, double *x1, double *y1, double *x2, double *y2, double *x3, double *y3) {
    const int steps = 180;
    double max_a = 0.0;
    for (int i = 0; i <= steps; ++i) {
        for (int j = 0; j <= steps; ++j) {
            double angle1 = 2 * M_PI * i / steps;
            double angle2 = 2 * M_PI * j / steps;
            double x_1 = a * cos(angle1);
            double y_1 = b * sin(angle1);
            double x_2 = a * cos(angle2);
            double y_2 = b * sin(angle2);
            double k = (y_1 - y_2) / (x_1 - x_2);
            double angle3 = atan2(-1/k, 1);
            if (angle3 < 0) angle3 += 2 * M_PI;
            double x_3 = a * cos(angle3);
            double y_3 = b * sin(angle3);
            double s1 = hypot(x_2 - x_1, y_2 - y_1);
            double s2 = hypot(x_3 - x_2, y_3 - y_2);
            double s3 = hypot(x_1 - x_3, y_1 - y_3);
            double area = triangle_area(s1, s2, s3);
            if (area > max_a) {
                max_a = area;
                *max_area = area;
                *x1 = x_1;
                *y1 = y_1;
                *x2 = x_2;
                *y2 = y_2;
                *x3 = x_3;
                *y3 = y_3;
            }
        }
    }
}

int main() {
    double a, b;
    printf("Enter the semi-major and semi-minor axes of the ellipse: ");
    scanf("%lf %lf", &a, &b);

    double max_area = 0.0;
    double x1, y1, x2, y2, x3, y3;

    find_largest_triangle(a, b, &max_area, &x1, &y1, &x2, &y2, &x3, &y3);

    printf("Largest inscribed triangle area: %.6f\n", max_area);
    printf("Vertices: (%.6f, %.6f), (%.6f, %.6f), (%.6f, %.6f)\n", x1, y1, x2, y2, x3, y3);

    return 0;
}