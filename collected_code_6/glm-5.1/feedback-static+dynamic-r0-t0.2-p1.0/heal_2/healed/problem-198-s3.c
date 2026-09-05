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
    double step = 2.0 * M_PI / n;

    for (int i = 0; i < n; i++) {
        double theta1 = i * step;
        Point p1;
        p1.x = a * cos(theta1);
        p1.y = b * sin(theta1);

        for (int j = 0; j < n; j++) {
            double theta2 = j * step;
            Point p2;
            p2.x = a * cos(theta2);
            p2.y = b * sin(theta2);

            double theta3 = theta2 + 2.0 * M_PI / 3.0;
            Point p3;
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

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <a> <b>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    double a = strtod(argv[1], &endptr1);
    if (*endptr1 != '\0' || a <= 0.0) {
        fprintf(stderr, "Invalid value for a. Must be a positive number.\n");
        return EXIT_FAILURE;
    }

    char *endptr2;
    double b = strtod(argv[2], &endptr2);
    if (*endptr2 != '\0' || b <= 0.0) {
        fprintf(stderr, "Invalid value for b. Must be a positive number.\n");
        return EXIT_FAILURE;
    }

    double area = find_largest_inscribed_triangle(a, b);
    printf("Largest inscribed triangle area: %.6f\n", area);

    return EXIT_SUCCESS;
}