#include <stdio.h>

int isEquilateral(int side1, int side2, int side3) {
    if (side1 == side2 && side2 == side3) {
        return 1;
    }
    return 0;
}

int main() {
    int side1, side2, side3;

    printf("Enter side 1: ");
    scanf("%d", &side1);

    printf("Enter side 2: ");
    scanf("%d", &side2);

    printf("Enter side 3: ");
    scanf("%d", &side3);

    if (isEquilateral(side1, side2, side3)) {
        printf("The triangle is equilateral.\n");
    } else {
        printf("The triangle is not equilateral.\n");
    }

    return 0;
}