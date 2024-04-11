#include <stdio.h>

double maxCuboidVolume(int sum) {
    double side = sum / 6.0;
    return side * side * side;
}

int main() {
    int sum;
    printf("Enter the sum of sides of the cuboid: ");
    scanf("%d", &sum);
    printf("The maximum volume of the cuboid is: %.2f\n", maxCuboidVolume(sum));
    return 0;
}