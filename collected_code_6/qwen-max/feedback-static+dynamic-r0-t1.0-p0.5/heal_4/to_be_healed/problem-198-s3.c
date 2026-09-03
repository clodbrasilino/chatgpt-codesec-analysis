#include <stdio.h>
#include <math.h>

double ellipse_area(double a, double b) {
    return M_PI * a * b;
}

double triangle_area(double base, double height) {
    return 0.5 * base * height;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10.392304845413264, got 16
  *  test case 1 failed: expected 4.639421805988064, got 70
  *  test case 2 failed: expected 105.2220865598093, got 18
  */

double find_largest_triangle(double a, double b) {
    double max_area = 0.0;
    for (double x = -a; x <= a; x += 0.01) {
        for (double y = -b; y <= b; y += 0.01) {
            if ((x * x / (a * a) + y * y / (b * b)) <= 1.0) {
                double area = triangle_area(2 * a, 2 * fabs(y));
                if (area > max_area) {
                    max_area = area;
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
    printf("The largest inscribed triangle area in the ellipse: %f\n", largest_triangle_area);
    return 0;
}