#include <stdio.h>

int isScalene(int a, int b, int c) {
    if (a != b && b != c && c != a) {
        return 1;
    }
    return 0;
}

int main() {
    int a, b, c;
    printf("Enter the sides of the triangle: ");
    scanf("%d %d %d", &a, &b, &c);
    if (isScalene(a, b, c)) {
        printf("The triangle is scalene.\n");
    } else {
        printf("The triangle is not scalene.\n");
    }
    return 0;
}