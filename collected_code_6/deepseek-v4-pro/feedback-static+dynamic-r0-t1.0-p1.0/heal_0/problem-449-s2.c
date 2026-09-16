#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double distance(Point a, Point b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

int is_valid_triangle(Point p1, Point p2, Point p3) {
    double side1 = distance(p1, p2);
    double side2 = distance(p2, p3);
    double side3 = distance(p3, p1);
    double epsilon = 1e-9;

    if (fabs(side1) < epsilon || fabs(side2) < epsilon || fabs(side3) < epsilon) {
        return 0;
    }

    if (side1 + side2 <= side3 + epsilon && side1 + side2 >= side3 - epsilon) {
        return 0;
    }
    if (side2 + side3 <= side1 + epsilon && side2 + side3 >= side1 - epsilon) {
        return 0;
    }
    if (side3 + side1 <= side2 + epsilon && side3 + side1 >= side2 - epsilon) {
        return 0;
    }

    return 1;
}

int main(void) {
    Point p1, p2, p3;
    int result;

    printf("Enter coordinates for point 1 (x y): ");
    if (scanf("%lf %lf", &p1.x, &p1.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Enter coordinates for point 2 (x y): ");
    if (scanf("%lf %lf", &p2.x, &p2.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Enter coordinates for point 3 (x y): ");
    if (scanf("%lf %lf", &p3.x, &p3.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = is_valid_triangle(p1, p2, p3);

    if (result) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return 0;
}