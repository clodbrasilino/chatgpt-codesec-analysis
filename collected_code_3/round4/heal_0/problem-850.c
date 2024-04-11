#include <stdio.h>

int isTrianglePossible(int angle1, int angle2, int angle3) {
    if(angle1 + angle2 + angle3 == 180) {
        return 1;
    }
    return 0;
}

int main() {
    int angle1, angle2, angle3;
    printf("Enter the three angles of the triangle: ");
    scanf("%d %d %d", &angle1, &angle2, &angle3);

    if(isTrianglePossible(angle1, angle2, angle3)) {
        printf("A triangle is possible with the given angles.\n");
    } else {
        printf("A triangle is not possible with the given angles.\n");
    }

    return 0;
}