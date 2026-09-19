#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return false;
    if (a + b > c && a + c > b && b + c > a) return true;
    return false;
}

int main() {
    int side1, side2, side3;
    bool valid;

    printf("Enter the three sides of the triangle: ");
    if (scanf("%d %d %d", &side1, &side2, &side3) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    valid = is_valid_triangle(side1, side2, side3);

    if (valid) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return 0;
}