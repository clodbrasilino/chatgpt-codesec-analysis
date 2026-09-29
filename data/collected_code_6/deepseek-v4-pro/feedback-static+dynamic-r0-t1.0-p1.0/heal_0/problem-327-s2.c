#include <stdio.h>
#include <stdbool.h>

bool is_isosceles(double side1, double side2, double side3) {
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        return false;
    }
    
    if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
        return false;
    }
    
    return (side1 == side2) || (side1 == side3) || (side2 == side3);
}

int main(void) {
    double a, b, c;
    int result;
    
    printf("Enter three sides of triangle: ");
    result = scanf("%lf %lf %lf", &a, &b, &c);
    
    if (result != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_isosceles(a, b, c)) {
        printf("Triangle is isosceles\n");
    } else {
        printf("Triangle is not isosceles\n");
    }
    
    return 0;
}