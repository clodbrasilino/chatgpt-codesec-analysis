
#include <stdio.h>

double maxVolume(double sumOfSides) {
    double side = sumOfSides / 6;
    double volume = side * side * side;
    return volume;
}

int main() {
    double sumOfSides;
    printf("Enter sum of sides: ");
    scanf("%lf", &sumOfSides);
    
    double maxVol = maxVolume(sumOfSides);
    printf("The maximum volume of a cuboid with sum of sides %.2lf is %.2lf\n", sumOfSides, maxVol);
    
    return 0;
}
