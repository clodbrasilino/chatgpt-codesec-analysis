#include <stdio.h>
#include <math.h>

double maxVolumeOfCuboid(double sideSum) {
    if (sideSum <= 0) {
        return 0;
    }
    
    double side = sideSum / 3.0;
    return side * side * side;
}

int main(void) {
    double sideSum;
    
    printf("Enter the sum of sides: ");
    if (scanf("%lf", &sideSum) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (sideSum < 0) {
        printf("Sum of sides cannot be negative\n");
        return 1;
    }
    
    double maxVolume = maxVolumeOfCuboid(sideSum);
    printf("Maximum volume: %.2f\n", maxVolume);
    
    return 0;
}