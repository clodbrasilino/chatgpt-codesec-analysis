#include <stdio.h>

double calculate_third_angle(double angle1, double angle2) {
    return 180.0 - (angle1 + angle2);
}

int main() {
    double angle1, angle2;

    printf("Enter the first angle: ");
    if (scanf("%lf", &angle1) != 1) {
        return 1;
    }

    printf("Enter the second angle: ");
    if (scanf("%lf", &angle2) != 1) {
        return 1;
    }

    double third_angle = calculate_third_angle(angle1, angle2);
    printf("The third angle is: %.2f\n", third_angle);

    return 0;
}