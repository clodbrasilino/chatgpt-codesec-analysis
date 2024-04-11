#include <stdio.h>

float findDiameter(float radius) {
    return 2*radius;
}

int main() {
    float radius;
    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);
    printf("Diameter of the circle is: %.2f\n", findDiameter(radius));
    return 0;
}