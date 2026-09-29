#include <stdio.h>

float findVolumeOfCube(float side) {
    return side * side * side;
}

int main() {
    float side;
    printf("Enter the length of a side of the cube: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &side);
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    float volume = findVolumeOfCube(side);
    printf("The volume of the cube is %.2f\n", volume);
    return 0;
}