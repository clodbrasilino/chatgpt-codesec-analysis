#include <stdio.h>

float findVolumeOfCube(float side) {
    return side * side * side;
}

int main() {
    float side;
    printf("Enter the length of a side of the cube: ");
    scanf("%f", &side);
    float volume = findVolumeOfCube(side);
    printf("The volume of the cube is %.2f\n", volume);
    return 0;
}