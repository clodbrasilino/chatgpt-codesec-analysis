#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double triangle_area(double a, double b, double theta1, double theta2, double theta3) {
    double x1 = a * cos(theta1);
    double y1 = b * sin(theta1);
    double x2 = a * cos(theta2);
    double y2 = b * sin(theta2);
    double x3 = a * cos(theta3);
    double y3 = b * sin(theta3);
    return 0.5 * fabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
}

double find_largest_inscribed_triangle(double a, double b) {
    if (a <= 0.0 || b <= 0.0) {
        return 0.0;
    }
    double max_area = 0.0;
    int num_steps = 1000;
    double step = 2.0 * M_PI / num_steps;
    double *areas = (double *)malloc(num_steps * num_steps * sizeof(double));
    if (areas == NULL) {
        return 0.0;
    }
    for (int i = 0; i < num_steps; i++) {
        for (int j = 0; j < num_steps; j++) {
            double theta1 = i * step;
            double theta2 = j * step;
            double theta3 = theta2 + 2.0 * M_PI / 3.0;
            areas[i * num_steps + j] = triangle_area(a, b, theta1, theta2, theta3);
        }
    }
    for (int i = 0; i < num_steps * num_steps; i++) {
        if (areas[i] > max_area) {
            max_area = areas[i];
        }
    }
    free(areas);
    areas = NULL;
    return max_area;
}

int main(void) {
    double a = 5.0;
    double b = 3.0;
    double area = find_largest_inscribed_triangle(a, b);
    printf("%f\n", area);
    return 0;
}