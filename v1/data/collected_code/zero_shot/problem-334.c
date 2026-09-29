#include <stdio.h>

int isValidTriangle(int side1, int side2, int side3) {
    // Check if all sides are positive
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        return 0;
    }
    // Check triangle inequality
    if (side1 + side2 > side3 && side2 + side3 > side1 && side3 + side1 > side2) {
        return 1;
    }
    return 0;
}

int main() {
    int side1, side2, side3;
    printf("Enter the three sides of the triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);
    if (isValidTriangle(side1, side2, side3)) {
        printf("Valid triangle.\n");
    } else {
        printf("Invalid triangle.\n");
    }
    return 0;
}