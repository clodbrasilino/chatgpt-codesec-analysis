#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(float a, float b, float c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    if ((a + b > c) && (b + c > a) && (c + a > b)) {
        return true;
    }
    return false;
}

int main(void) {
    float side1, side2, side3;
    
    printf("Enter three sides of a triangle: ");
    if (scanf("%f %f %f", &side1, &side2, &side3) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_valid_triangle(side1, side2, side3)) {
        printf("The triangle is valid\n");
    } else {
        printf("The triangle is not valid\n");
    }
    
    return 0;
}