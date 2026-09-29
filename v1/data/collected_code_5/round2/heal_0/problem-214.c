#include <stdio.h>
#define PI 3.14159265

double radiansToDegrees(double radians) {
    return radians * (180.0 / PI);
}

int main() {
    double radians;
    printf("Enter value in radians: ");
    if (scanf("%lf", &radians) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Value in degrees: %.2lf\n", radiansToDegrees(radians));

    return 0;
}