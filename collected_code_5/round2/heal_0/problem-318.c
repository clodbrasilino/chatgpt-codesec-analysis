#include <stdio.h>

double MaximumCuboidVolume(double sumOfSides){
    if (sumOfSides < 0) {
        return -1;
    }

    double side = sumOfSides / 3.0;
    double volume = side * side * side;

    return volume;
}

int main(){
    double sumOfSides;
    printf("Enter the sum of sides of a cuboid: ");
    scanf("%lf", &sumOfSides);
    double volume = MaximumCuboidVolume(sumOfSides);
    
    if(volume == -1){
        printf("Error: Sum of sides cannot be a negative number\n");
        return 1;
    }

    printf("Maximum volume of cuboid with given sum of sides is %.2lf\n", volume);

    return 0;
}