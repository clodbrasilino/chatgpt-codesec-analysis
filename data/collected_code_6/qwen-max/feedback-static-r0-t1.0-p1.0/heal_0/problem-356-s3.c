#include <stdio.h>

double findThirdAngle(double angle1, double angle2) {
    return 180.0 - (angle1 + angle2);
}

int main() {
    double angle1, angle2;
    printf("Enter the first angle of the triangle: ");
    if (scanf("%lf", &angle1) != 1) return 1;
    printf("Enter the second angle of the triangle: ");
    if (scanf("%lf", &angle2) != 1) return 1;
    
    double thirdAngle = findThirdAngle(angle1, angle2);
    printf("The third angle is: %.2f\n", thirdAngle);

    return 0;
}