#include <stdio.h>

int isTrianglePossible(int angle1, int angle2, int angle3) {
    if (angle1 + angle2 + angle3 == 180) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int angle1, angle2, angle3;
    printf("Enter three angles of the triangle: ");
    scanf("%d %d %d", &angle1, &angle2, &angle3);

    if (isTrianglePossible(angle1, angle2, angle3)) {
        printf("Triangle is possible.\n");
    } else {
        printf("Triangle is not possible.\n");
    }

    return 0;
}