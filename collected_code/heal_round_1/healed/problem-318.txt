#include <stdio.h>

double maxVolume(double sumOfSides) {
    double side = sumOfSides / 6;
    double volume = side * side * side;
    return volume;
}

int main() {
    double sumOfSides = 0.0;

    printf("Enter sum of sides: ");
    if(scanf("%lf", &sumOfSides) != 1) {
        printf("Failed to read the sum of sides.\n");
        return 1;
    }

    double maxVol = maxVolume(sumOfSides);

    printf("The maximum volume of a cuboid with sum of sides %.2lf is %.2lf\n", sumOfSides, maxVol);
    
    return 0;
}