#include <stdio.h>

float areaOfRombus(float d1, float d2) {
    return 0.5 * d1 * d2;
}

int main() {
    float d1, d2;
    printf("Enter the lengths of the diagonals of the rombus: ");
    scanf("%f %f", &d1, &d2);
    printf("The area of the rombus is: %.2f\n", areaOfRombus(d1, d2));
    return 0;
}