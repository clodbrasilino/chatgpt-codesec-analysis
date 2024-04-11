#include <stdio.h>

double triangularPrismVolume(double base, double height, double length) {
    return 0.5 * base * height * length;
}

int main() {
    double base, height, length, volume;

    printf("Enter base of the triangular prism: ");
    scanf("%lf", &base);

    printf("Enter height of the triangular prism: ");
    scanf("%lf", &height);

    printf("Enter length of the triangular prism: ");
    scanf("%lf", &length);

    volume = triangularPrismVolume(base, height, length);

    printf("Volume of the triangular prism is: %.2lf\n", volume);

    return 0;
}