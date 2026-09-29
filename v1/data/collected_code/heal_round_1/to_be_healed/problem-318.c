
#include <stdio.h>

double maxVolume(double sumOfSides) {
    double side = sumOfSides / 6;
    double volume = side * side * side;
    return volume;
}

int main() {
    double sumOfSides;
    printf("Enter sum of sides: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'sumOfSides' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &sumOfSides);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'sumOfSides' is initialized [premium-bughuntingUninit]
     */
    double maxVol = maxVolume(sumOfSides);
    /* Possible weaknesses found:
     *  Cannot determine that 'sumOfSides' is initialized [premium-bughuntingUninit]
     */
    printf("The maximum volume of a cuboid with sum of sides %.2lf is %.2lf\n", sumOfSides, maxVol);
    
    return 0;
}
