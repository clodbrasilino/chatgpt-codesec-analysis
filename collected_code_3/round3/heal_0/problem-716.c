#include <stdio.h>

float perimeter_of_rhombus(float side) {
    return 4 * side;
}

int main() {
    float side;
    printf("Enter the side of the rhombus: ");
    scanf("%f", &side);
    printf("Perimeter of the rhombus: %.2f\n", perimeter_of_rhombus(side));
    return 0;
}