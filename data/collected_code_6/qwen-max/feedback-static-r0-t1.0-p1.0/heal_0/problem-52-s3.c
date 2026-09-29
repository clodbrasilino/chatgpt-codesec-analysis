#include <stdio.h>

double calculate_area_of_parallelogram(double base, double height) {
    return base * height;
}

int main() {
    double base = 5.0;
    double height = 3.0;
    double area = calculate_area_of_parallelogram(base, height);
    printf("Area of the parallelogram: %f\n", area);
    return 0;
}