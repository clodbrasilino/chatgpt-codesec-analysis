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

double find_largest_inscribed_triangle(double a, double b) {
    if (a <= 0.0 || b <= 0.0) {
        return 0.0;
    }

    int n = 1000000;
    double max_area = 0.0;
    double theta1 = 0.0;
    double step = 2.0 * M_PI / n;

    Point p1, p2, p3;

    p1.x = a * cos(theta1);
    p1.y = b * sin(theta1);

    for (int i = 1; i < n; i++) {
        double theta2 = i * step;
        p2.x = a * cos(theta2);
        p2.y = b * sin(theta2);

        for (int j = i + 1; j < n; j++) {
            double theta3 = j * step;
            p3.x = a * cos(theta3);
            p3.y = b * sin(theta3);

            double area = triangle_area(p1, p2, p3);
            if (area > max_area) {
                max_area = area;
            }
        }
    }

    return max_area;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <semi_major_axis> <semi_minor_axis>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    double a = strtod(argv[1], &endptr1);
    double b = strtod(argv[2], &endptr2);

    if (*endptr1 != '\0' || *endptr2 != '\0' || a <= 0.0 || b <= 0.0) {
        fprintf(stderr, "Error: Semi-major and semi-minor axes must be positive numbers.\n");
        return EXIT_FAILURE;
    }

    double area = find_largest_inscribed_triangle(a, b);
    printf("Largest inscribed triangle area: %f\n", area);
    printf("Analytical maximum area: %f\n", 1.5 * a * b * sqrt(3.0) / 2.0);

    return EXIT_SUCCESS;
}