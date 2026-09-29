#include <stdio.h>

int isTriangleValid(int x, int y, int z) {
    if (x + y > z && x + z > y && y + z > x) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int x, y, z;
    printf("Enter three sides of triangle: ");
    scanf("%d%d%d", &x, &y, &z);

    if (isTriangleValid(x, y, z)) {
        printf("Triangle is valid.\n");
    } else {
        printf("Triangle is not valid.\n");
    }

    return 0;
}