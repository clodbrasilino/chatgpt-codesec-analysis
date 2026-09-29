#include <stdio.h>

int isTrianglePossible(int angle1, int angle2, int angle3) {
    int sum = angle1 + angle2 + angle3;

    if(sum == 180 && angle1 > 0 && angle2 > 0 && angle3 > 0) {
        return 1;
    }

    return 0;
}

int main() {
    int angle1, angle2, angle3;

    printf("Enter angle 1: ");
    scanf("%d", &angle1);

    printf("Enter angle 2: ");
    scanf("%d", &angle2);

    printf("Enter angle 3: ");
    scanf("%d", &angle3);

    if(isTrianglePossible(angle1, angle2, angle3)) {
        printf("A triangle with the provided angles is possible.\n");
    } else {
        printf("A triangle with the provided angles is not possible.\n");
    }

    return 0;
}