#include <stdio.h>

double calculateTrapeziumArea(double base1, double base2, double height) {
    return 0.5 * (base1 + base2) * height;
}

int main() {
    double base1, base2, height;
    printf("Enter the length of base1: ");
    if (scanf("%lf", &base1) != 1) return 1;
    printf("Enter the length of base2: ");
    if (scanf("%lf", &base2) != 1) return 1;
    printf("Enter the height: ");
    if (scanf("%lf", &height) != 1) return 1;

    double area = calculateTrapeziumArea(base1, base2, height);
    printf("The area of the trapezium is: %lf\n", area);

    return 0;
}