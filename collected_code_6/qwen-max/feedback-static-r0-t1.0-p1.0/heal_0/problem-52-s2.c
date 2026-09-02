#include <stdio.h>

double calculate_area(double base, double height) {
    return base * height;
}

int main() {
    double base, height;
    printf("Enter the base of the parallelogram: ");
    if (scanf("%lf", &base) != 1) {
        return 1;
    }
    printf("Enter the height of the parallelogram: ");
    if (scanf("%lf", &height) != 1) {
        return 1;
    }
    double area = calculate_area(base, height);
    printf("The area of the parallelogram is: %f\n", area);
    return 0;
}