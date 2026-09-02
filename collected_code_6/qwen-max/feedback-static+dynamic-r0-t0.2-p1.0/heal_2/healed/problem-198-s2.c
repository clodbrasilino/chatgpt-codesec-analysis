#include <stdio.h>
#include <math.h>

double ellipse_area(double a, double b) {
    return M_PI * a * b;
}

double triangle_area(double a, double b, double c) {
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double find_largest_triangle(double a, double b) {
    double max_area = 0.0;
    for (double x1 = -a; x1 <= a; x1 += 0.01) {
        for (double y1 = -b; y1 <= b; y1 += 0.01) {
            if (x1 * x1 / (a * a) + y1 * y1 / (b * b) > 1) continue;
            for (double x2 = -a; x2 <= a; x2 += 0.01) {
                for (double y2 = -b; y2 <= b; y2 += 0.01) {
                    if (x2 * x2 / (a * a) + y2 * y2 / (b * b) > 1) continue;
                    for (double x3 = -a; x3 <= a; x3 += 0.01) {
                        for (double y3 = -b; y3 <= b; y3 += 0.01) {
                            if (x3 * x3 / (a * a) + y3 * y3 / (b * b) > 1) continue;
                            double side1 = hypot(x2 - x1, y2 - y1);
                            double side2 = hypot(x3 - x2, y3 - y2);
                            double side3 = hypot(x1 - x3, y1 - y3);
                            double area = triangle_area(side1, side2, side3);
                            if (area > max_area) {
                                max_area = area;
                            }
                        }
                    }
                }
            }
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