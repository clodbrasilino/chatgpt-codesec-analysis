#include <stdio.h>

float cube_lateral_surface_area(float side) {
    return 4.0f * side * side;
}

int main(void) {
    float side = 5.0f;
    float area = cube_lateral_surface_area(side);
    printf("Lateral surface area: %.2f\n", area);
    return 0;
}