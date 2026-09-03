#include <stdio.h>
#include <math.h>

double ellipse_area(double a, double b) {
    return M_PI * a * b;
}

double triangle_area(double a, double h) {
    return 0.5 * a * h;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 105.2220865598093, got 3.8971142768859863
  *  test case 0 failed: expected 10.392304845413264, got 3.4641015529632568
  *  test case 1 failed: expected 4.639421805988064, got 15.155444145202637
  */

double find_largest_triangle(double a, double b) {
    double max_area = 0.0;
    for (double theta = 0; theta <= 2 * M_PI; theta += 0.01) {
        double x1 = a * cos(theta);
        double y1 = b * sin(theta);
        double x2 = a * cos(theta + M_PI / 3);
        double y2 = b * sin(theta + M_PI / 3);
        double x3 = a * cos(theta + 2 * M_PI / 3);
        double y3 = b * sin(theta + 2 * M_PI / 3);

        double area = fabs(0.5 * (x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)));
        if (area > max_area) {
            max_area = area;
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