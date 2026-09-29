#include <stdio.h>

int isEquilateral(int side1, int side2, int side3) {
    if(side1 == side2 && side2 == side3) {
        return 1;
    }
    return 0;
}

int main() {
    int side1, side2, side3;
    printf("Enter the sides of the triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);

    if(isEquilateral(side1, side2, side3)) {
        printf("The triangle is equilateral.\n");
    } else {
        printf("The triangle is not equilateral.\n");
    }

    return 0;
}