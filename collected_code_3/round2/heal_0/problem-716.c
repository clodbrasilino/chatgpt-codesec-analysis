#include <stdio.h>

float perimeterOfRombus(float side) {
    return 4 * side;
}

int main() {
    float side;
    printf("Enter the side of the rombus: ");
    scanf("%f", &side);
    printf("Perimeter of the rombus: %.2f\n", perimeterOfRombus(side));
    return 0;
}