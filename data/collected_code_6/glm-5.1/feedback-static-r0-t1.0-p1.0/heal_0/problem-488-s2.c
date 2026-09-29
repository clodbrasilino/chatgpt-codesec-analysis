#include <stdio.h>
#include <math.h>

double calculate_pentagon_area(double side) {
    if (side <= 0.0) {
        return -1.0;
    }
    return (5.0 * side * side) / (4.0 * tan(M_PI / 5.0));
}

int main() {
    double side;
    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    double area = calculate_pentagon_area(side);
    if (area < 0.0) {
        fprintf(stderr, "Invalid side length\n");
        return 1;
    }
    printf("%f\n", area);
    return 0;
}