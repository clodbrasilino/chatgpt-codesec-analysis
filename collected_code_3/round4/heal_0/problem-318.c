#include <stdio.h>

double maxVolume(double sum) {
    double side = sum / 3.0;
    return side * side * side;
}

int main() {
    double sum;
    printf("Enter the sum of sides of the cuboid: ");
    scanf("%lf", &sum);
    printf("The maximum volume of the cuboid is: %.2lf\n", maxVolume(sum));
    return 0;
}