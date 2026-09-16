#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(int a, int b, int c) {
    return a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a;
}

int main() {
    int side1, side2, side3;
    
    printf("Enter three sides of the triangle: ");
    if (scanf("%d %d %d", &side1, &side2, &side3) != 3) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    if (is_valid_triangle(side1, side2, side3)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }
    
    return 0;
}