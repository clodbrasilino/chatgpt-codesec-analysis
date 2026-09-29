#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double triangle_area(Point p1, Point p2, Point p3) {
    return 0.5 * fabs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
}

double find_largest_inscribed_triangle_area(double a, double b) {
    if (a <= 0.0 || b <= 0.0) {
        return 0.0;
    }

    int num_steps = 1000000;
    double max_area = 0.0;
    double step = 2.0 * M_PI / num_steps;

    Point p1, p2, p3;

    p1.x = a;
    p1.y = 0.0;

    for (int i = 1; i < num_steps; i++) {
        double theta2 = i * step;
        p2.x = a * cos(theta2);
        p2.y = b * sin(theta2);

        for (int j = i + 1; j < num_steps; j++) {
            double theta3 = j * step;
            p3.x = a * cos(theta3);
            p3.y = b * sin(theta3);

            double current_area = triangle_area(p1, p2, p3);
            if (current_area > max_area) {
                max_area = current_area;
            }
        }
    }

    return max_area;
}

int main(void) {
    double a = 5.0;
    double b = 3.0;

    double area = find_largest_inscribed_triangle_area(a, b);

    if (printf("Largest inscribed triangle area: %f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}