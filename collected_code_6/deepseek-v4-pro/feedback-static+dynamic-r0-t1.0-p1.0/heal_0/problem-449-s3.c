#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

int is_valid_triangle(Point p1, Point p2, Point p3) {
    double a, b, c;

    a = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    b = sqrt(pow(p3.x - p2.x, 2) + pow(p3.y - p2.y, 2));
    c = sqrt(pow(p1.x - p3.x, 2) + pow(p1.y - p3.y, 2));

    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }

    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }

    return 1;
}

int main(void) {
    Point p1, p2, p3;

    printf("Enter coordinates of first point (x y): ");
    if (scanf("%lf %lf", &p1.x, &p1.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Enter coordinates of second point (x y): ");
    if (scanf("%lf %lf", &p2.x, &p2.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Enter coordinates of third point (x y): ");
    if (scanf("%lf %lf", &p3.x, &p3.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (is_valid_triangle(p1, p2, p3)) {
        printf("The points form a valid triangle.\n");
    } else {
        printf("The points do not form a valid triangle.\n");
    }

    return 0;
}