#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool canFormTriangle(int a, int b, int c) {
    return (a > 0 && b > 0 && c > 0 && a + b + c == 180);
}

int main() {
    int angle1, angle2, angle3;
    printf("Enter three angles of a triangle: ");
    if (scanf("%d %d %d", &angle1, &angle2, &angle3) != 3) {
        printf("Invalid input\n");
        return 1;
    }

    if (canFormTriangle(angle1, angle2, angle3)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}