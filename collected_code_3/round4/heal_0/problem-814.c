#include <stdio.h>

float rombusArea(float d1, float d2) {
    return (d1 * d2) / 2;
}

int main() {
    float d1, d2;
    printf("Enter the lengths of the diagonals: ");
    scanf("%f %f", &d1, &d2);
    printf("The area of the rombus is: %.2f\n", rombusArea(d1, d2));
    return 0;
}