#include <stdio.h>
#include <stdbool.h>

bool is_isosceles(int a, int b, int c) {
    return (a == b || b == c || a == c);
}

int main() {
    int side1, side2, side3;
    printf("Enter the three sides of the triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);

    if (is_isosceles(side1, side2, side3)) {
        printf("The triangle is isosceles.\n");
    } else {
        printf("The triangle is not isosceles.\n");
    }

    return 0;
}