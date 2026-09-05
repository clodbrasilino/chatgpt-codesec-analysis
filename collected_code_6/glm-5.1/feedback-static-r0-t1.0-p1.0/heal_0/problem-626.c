#include <stdio.h>
#include <math.h>

double largest_triangle_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    if (radius == 0.0) {
        return 0.0;
    }
    return radius * radius;
}

int main(int argc, char *argv[]) {
    double r = 5.0;
    double area = largest_triangle_area(r);
    if (area < 0.0) {
        printf("Invalid radius\n");
    } else {
        printf("Largest triangle area: %f\n", area);
    }
    return 0;
}