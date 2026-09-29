#include <stdio.h>

int isTriangleValid(int a, int b, int c) {
    if (a + b <= c || a + c <= b || b + c <= a)
        return 0;
    else
        return 1;
}

int main() {
    int a, b, c;
    printf("Enter the sides of the triangle: ");
    scanf("%d%d%d", &a, &b, &c);
    if (isTriangleValid(a, b, c))
        printf("The triangle is valid.\n");
    else
        printf("The triangle is not valid.\n");
    return 0;
}