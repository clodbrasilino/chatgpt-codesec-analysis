#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

double cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int is_valid_triangle(Point a, Point b, Point c) {
    double cp = cross_product(a, b, c);
    if (cp < 0) cp = -cp;
    return cp > 1e-9;
}

int main(void) {
    Point p1, p2, p3;
    
    if (scanf("%lf %lf %lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y) != 6) {
        return EXIT_FAILURE;
    }
    
    if (is_valid_triangle(p1, p2, p3)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
    
    return EXIT_SUCCESS;
}