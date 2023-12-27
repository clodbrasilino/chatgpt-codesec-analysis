#include <stdio.h>

int isValidTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    int side1 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    int side2 = (x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2);
    int side3 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);

    if (side1 + side2 > side3 && side2 + side3 > side1 && side1 + side3 > side2) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;

    printf("Enter coordinates of first point: ");
    scanf("%d %d", &x1, &y1);

    printf("Enter coordinates of second point: ");
    scanf("%d %d", &x2, &y2);

    printf("Enter coordinates of third point: ");
    scanf("%d %d", &x3, &y3);

    if (isValidTriangle(x1, y1, x2, y2, x3, y3)) {
        printf("The given points form a valid triangle.\n");
    }
    else {
        printf("The given points do not form a valid triangle.\n");
    }

    return 0;
}