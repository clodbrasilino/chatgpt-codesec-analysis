#include <stdio.h>
#include <stdlib.h>

double find_largest_triangle(double radius) {
    if (radius < 0.0) {
        exit(EXIT_FAILURE);
    }
    return radius * radius;
}

int main(void) {
    double r = 5.0;
    double area = find_largest_triangle(r);
    printf("%f\n", area);
    return 0;
}