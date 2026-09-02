#include <stdio.h>
#include <math.h>

double pentagon_area(double side) {
    return (sqrt(5 * (5 + 2 * sqrt(5))) * side * side) / 4;
}

int main() {
    double side = 5.0;
    double area = pentagon_area(side);
    printf("The area of the pentagon is: %f\n", area);
    return 0;
}